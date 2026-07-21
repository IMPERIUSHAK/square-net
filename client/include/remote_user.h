#ifndef REMOTE_USER_H
#define REMOTE_USER_H

#include "user.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "protocol.h"

#define MAXUSERS 3

typedef struct {
    UserData users[MAXUSERS];
    int count;
    pthread_mutex_t mutex;
} RemoteUsers;

#endif