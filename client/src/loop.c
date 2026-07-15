#include "loop.h"


void run_loop(Window *app, User *user, bool *isRunning, pthread_mutex_t *isRunningMutex){

    pthread_mutex_lock(isRunningMutex);
    bool running = *isRunning;
    pthread_mutex_unlock(isRunningMutex);


    while (running){
        
        pthread_mutex_lock(isRunningMutex);
        running = *isRunning;
        pthread_mutex_unlock(isRunningMutex);

        SDL_SetRenderDrawColor(app->render, 0, 0, 0, 255);
        SDL_RenderClear(app->render);
        DrawUser(app->render, user);
        SDL_RenderPresent(app->render);

    }

}