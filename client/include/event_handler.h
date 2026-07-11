#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "window.h"
#include "user.h"


void handle_events(Window *app, User *user, bool *isRunning);

void handle_user_events(User *user, SDL_Event *event);

#endif

