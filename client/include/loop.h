#ifndef LOOP_H
#define LOOP_H

#include "window.h"
#include "user.h"
#include "event_handler.h"
#include "pthread.h"

void run_loop(Window *screen, User *user, bool *isRunning, pthread_mutex_t *isRunningMutex);

#endif