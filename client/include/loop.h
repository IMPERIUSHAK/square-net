#ifndef LOOP_H
#define LOOP_H

#include "window.h"
#include "user.h"
#include "event_handler.h"
#include "pthread.h"
#include "remote_user.h"

void run_loop(Window *app, User *user, bool *isRunning, pthread_mutex_t *isRunningMutex, RemoteUsers *remote);

#endif