#include "event_handler.h"

void handle_user_events(User *user, SDL_Event *event){

    switch (event->key.keysym.scancode)
    {
    case SDL_SCANCODE_D:
        MoveUser(user, 5, 0);
        break;
    
    case SDL_SCANCODE_A:
        MoveUser(user, -5, 0);
        break;
    
    case SDL_SCANCODE_W:
        MoveUser(user, 0, -5);
        break;
    
    case SDL_SCANCODE_S:
        MoveUser(user, 0, 5);
        break;
    default:
        break;
    }
}


void handle_events(Window *app, User *user, bool *isRunning){
    
    while (SDL_PollEvent(app->event)) {
    
        if (app->event->type == SDL_QUIT || app->event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            *isRunning = false;
        }
    
        if (app->event->type == SDL_KEYDOWN) {
    
            handle_user_events(user, app->event);
        }
    }
}