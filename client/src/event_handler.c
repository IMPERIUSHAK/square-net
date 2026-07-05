#include "event_handler.h"

void handle_default_buttons(SDL_Event *event, bool *isRunning){

    while(SDL_PollEvent(event)){

        if (event->type == SDL_QUIT || event->key.keysym.scancode == SDL_SCANCODE_ESCAPE){
            (*isRunning) = false;
        }

    }

}