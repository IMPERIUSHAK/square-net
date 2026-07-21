#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include <netinet/in.h>
#define MAXUSERS 3

typedef struct {

    int x;
    int y;
    char ip[16];
    int port;
    int connfd;

}UserData;

typedef struct{

    int *userCount;
    int connfd;
    UserData (*users)[MAXUSERS];
    pthread_mutex_t *usersMutex;
    struct sockaddr_in cliaddr;
    pthread_mutex_t *sendMutexes;
    
}ClientThreadArgs;


int checkUser(UserData **users, UserData *user);
void updateUser(UserData **users, UserData *user, int *userCount);
void addUser(UserData **users, UserData *user, int *userCount);

#endif