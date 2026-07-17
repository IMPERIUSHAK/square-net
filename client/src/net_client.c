#include "net_client.h"
#include "protocol.h"
#include "time.h"
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