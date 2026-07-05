#include "loop.h"
#include "event_handler.h"

void run_loop(Window *app){

    bool isRunning = true;

    while (isRunning){

        handle_default_buttons(app->event, &isRunning);

        SDL_SetRenderDrawColor(app->render, 0, 0, 0, 255);
        SDL_RenderClear(app->render);
        SDL_RenderPresent(app->render);

    }

}