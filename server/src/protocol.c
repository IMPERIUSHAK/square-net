#include "protocol.h"
#include "server.h"

int checkUser(UserData **users, UserData *user){

    for (int i = 0; i < MAXUSERS; i++){
        if ((strcmp((*users)[i].ip, user->ip) == 0) && ((*users)[i].port == user->port)){
            return i;
        }
    }

    return -1;
}

void addUser(UserData **users, UserData *user, int *userCount){

    strcpy((*users)[*userCount].ip, user->ip);
    (*users)[*userCount].port = user->port;
    (*users)[*userCount].x = user->x;
    (*users)[*userCount].y = user->y;
    
    (*userCount)++;
}

void updateUser(UserData **users, UserData *user, int *userCount){
    (*users)[*userCount].x = user->x;
    (*users)[*userCount].y = user->y;
}