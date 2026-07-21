#include "net_client.h"
#include "protocol.h"
#include "time.h"
#include "remote_user.h"
bool net_client_connect(NetClient *client) {
    
    client->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->sockfd < 0) {
        perror("socket");
        return false;
    }

    memset(&client->server_addr, 0, sizeof(client->server_addr));
    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_IP, &client->server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(client->sockfd);
        return false;
    }

    if (connect(client->sockfd, (struct sockaddr *)&client->server_addr,
                sizeof(client->server_addr)) < 0) {
        perror("connect");
        close(client->sockfd);
        return false;
    }

    client->connected = true;
    return true;
}

void* handle_connection(void *arg) {
    
    ConnectionThreadArgs *args = (ConnectionThreadArgs *)arg;
    NetClient *netclient = args->netclient;

    if (!net_client_connect(netclient)) {
        fprintf(stderr, "Failed to connect to server\n");
        return NULL;
    }

    printf("Connected to server %s:%d\n", SERVER_IP, SERVER_PORT);

    RecvThreadArgs *rargs = malloc(sizeof(RecvThreadArgs));
    rargs->netclient = netclient;
    rargs->remote = args->remote;

    pthread_t recv_tid;
    pthread_create(&recv_tid, NULL, handle_recv, rargs);
    pthread_detach(recv_tid);
    
    while (1) {

        pthread_mutex_lock(args->isRunningMutex);
        bool running = *args->isRunning;
        pthread_mutex_unlock(args->isRunningMutex);

        if (!running) break;

        UserData data;
        pthread_mutex_lock(args->userMutex);
        data.x = args->user->user_rect.x;
        data.y = args->user->user_rect.y;
        pthread_mutex_unlock(args->userMutex);
        
        ssize_t sent = send(netclient->sockfd, &data, sizeof(data), 0);
        if (sent < 0){
            perror("send");
            break;
        }

        printf("Sent coords: x=%d, y=%d\n", data.x, data.y);
        usleep(16);
    }

    netclient->connected = false;
    close(netclient->sockfd);
    return NULL;
}

static ssize_t recv_all(int fd, void *buf, size_t size) {
    size_t total = 0;
    while (total < size) {
        ssize_t n = recv(fd, (char*)buf + total, size - total, 0);
        if (n <= 0) return n;
        total += n;
    }
    return total;
}

void* handle_recv(void *arg) {
    RecvThreadArgs *rargs = (RecvThreadArgs *)arg;
    int fd = rargs->netclient->sockfd;

    while (1) {
        uint32_t netcount;
        if (recv_all(fd, &netcount, sizeof(netcount)) != sizeof(netcount)) break;
        int count = (int)ntohl(netcount);

        if (count < 0 || count > MAXUSERS) break;

        UserData buf[MAXUSERS];
        if (recv_all(fd, buf, count * sizeof(UserData)) != (ssize_t)(count * sizeof(UserData))) break;

        pthread_mutex_lock(&rargs->remote->mutex);
        memcpy(rargs->remote->users, buf, count * sizeof(UserData));
        rargs->remote->count = count;
        pthread_mutex_unlock(&rargs->remote->mutex);
    }

    printf("Disconnected from server (recv thread)\n");
    return NULL;
}