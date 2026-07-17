#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "stdio.h"
#include "stdlib.h"

typedef struct {

    int x;
    int y;
    char ip[16];
    int port;
    int connfd;
}UserData;

int checkUser(UserData **users, UserData *user);
void updateUser(UserData **users, UserData *user, int *userCount);
void addUser(UserData **users, UserData *user, int *userCount);

#endif