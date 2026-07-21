#ifndef NET_CLIENT_H
#define NET_CLIENT_H

#include "user.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "remote_user.h"

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 720

typedef struct {
    int sockfd;
    struct sockaddr_in server_addr;
    bool connected;
} NetClient;

typedef struct {
    NetClient *netclient;
    bool *isRunning;
    pthread_mutex_t *isRunningMutex;
    User *user;
    pthread_mutex_t *userMutex;
    RemoteUsers *remote;
} ConnectionThreadArgs;

typedef struct {
    NetClient *netclient;
    RemoteUsers *remote;
} RecvThreadArgs;         

void* handle_connection(void* arg);
void* handle_recv(void* arg);
bool net_client_connect(NetClient *client);

#endif