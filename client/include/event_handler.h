#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "window.h"
#include "user.h"
#include "pthread.h"

typedef struct {
    Window *screen;
    User *user;
    bool *isRunning;
    pthread_mutex_t *isRunningMutex;
    pthread_mutex_t *userMutex;
} EventThreadArgs;


void *handle_events(void *arg);

void handle_user_events(User *user, SDL_Event *event);

#endif

