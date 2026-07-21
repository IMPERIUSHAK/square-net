#include "handle_client.h"


static ssize_t recv_all(int fd, void *buf, size_t size) {
    size_t total = 0;
    while (total < size) {
        ssize_t n = recv(fd, (char*)buf + total, size - total, 0);
        if (n <= 0) return n;
        total += n;
    }
    return total;
}

static ssize_t send_all(int fd, const void *buf, size_t size) {
    size_t total = 0;
    while (total < size) {
        ssize_t n = send(fd, (const char*)buf + total, size - total, MSG_NOSIGNAL);
        if (n <= 0) return n;
        total += n;
    }
    return total;
}

void* handle_client(void *arg){

    ClientThreadArgs *targs = (ClientThreadArgs *)arg;
    int connfd = targs->connfd;

    UserData incoming = {0};
    incoming.port = ntohs(targs->cliaddr.sin_port);
    
    inet_ntop(AF_INET, &targs->cliaddr.sin_addr, incoming.ip, sizeof(incoming.ip));
    incoming.connfd = connfd;

    printf("connection from %s, port %d\n", incoming.ip, incoming.port);

    pthread_mutex_lock(targs->usersMutex);
    int idx = -1;
    for (int i = 0; i < *targs->userCount; i++) {
        if ((strcmp((*targs->users)[i].ip, incoming.ip) == 0) && (incoming.port == (*targs->users)[i].port)) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        if (*targs->userCount < MAXUSERS) {
            idx = *targs->userCount;
            (*targs->users)[idx] = incoming;
            (*targs->userCount)++;
            printf("hello, new user #%d\n", idx);
        } else {
            printf("Reached the limit of users\n");
            pthread_mutex_unlock(targs->usersMutex);
            close(connfd);
            free(targs);
            return NULL;
        }
    } else {
        (*targs->users)[idx].connfd = connfd;
    }
    pthread_mutex_unlock(targs->usersMutex);

    UserData buf;

    while (recv_all(connfd, &buf, sizeof(buf)) == sizeof(buf)) {
        
        pthread_mutex_lock(targs->usersMutex);
        (*targs->users)[idx].x = buf.x;
        (*targs->users)[idx].y = buf.y;

        int count = *targs->userCount;
        UserData snapshot[MAXUSERS];
        memcpy(snapshot, *targs->users, count * sizeof(UserData));
        pthread_mutex_unlock(targs->usersMutex);

        printf("Server got data: user #%d -> x=%d, y=%d\n", idx, buf.x, buf.y);

        uint32_t netcount = htonl((uint32_t)count);

        for (int i = 0; i < count; i++) {

            if (i == idx) continue;
            pthread_mutex_lock(&targs->sendMutexes[i]);
            
            ssize_t s1 = send_all(snapshot[i].connfd, &netcount, sizeof(netcount));
            ssize_t s2 = (s1 > 0) ? send_all(snapshot[i].connfd, snapshot, count * sizeof(UserData)) : -1;
            
            pthread_mutex_unlock(&targs->sendMutexes[i]);

            if (s1 <= 0 || s2 <= 0) {
                printf("failed to send to user #%d\n", i);
            }
        }

        // pthread_mutex_lock(targs->usersMutex);

        // printf("==========================USERS==========================\n");
        // for (int i = 0; i < *targs->userCount; i++) {
        //     printf("||User ip: %-15s port: %-6d x = %d y= %d  ||\n",
        //         (*targs->users)[i].ip, (*targs->users)[i].port,
        //         (*targs->users)[i].x, (*targs->users)[i].y);
        // }
        // printf("===========================================================\n\n");

        // pthread_mutex_unlock(targs->usersMutex);
    }

    printf("user #%d (%s) disconnected\n", idx, incoming.ip);
    close(connfd);
    free(targs);
    
    return NULL;

}