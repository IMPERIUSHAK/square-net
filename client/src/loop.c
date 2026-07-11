#include "loop.h"


void run_loop(Window *app, User *user){

    bool isRunning = true;

    while (isRunning){

        handle_events(app, user, &isRunning);
        
        SDL_SetRenderDrawColor(app->render, 0, 0, 0, 255);
        SDL_RenderClear(app->render);
        DrawUser(app->render, user);
        SDL_RenderPresent(app->render);

    }

}