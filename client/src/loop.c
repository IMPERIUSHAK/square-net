#include "loop.h"

bool run_loop(Window *app){

    bool isRunning = true;

    

    while (isRunning){

        event_handler(app->event);

        SDL_SetRenderDrawColor(app->render, 0, 0, 0, 255);
        SDL_RenderClear(app->render);
        SDL_RenderPresent(app->render);

    }

}