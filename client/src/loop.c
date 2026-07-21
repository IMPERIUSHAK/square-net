#include "loop.h"

void run_loop(Window *app, User *user, bool *isRunning, pthread_mutex_t *isRunningMutex, RemoteUsers *remote){

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


        UserData snapshot[MAXUSERS];
        int count;
        pthread_mutex_lock(&remote->mutex);
        count = remote->count;
        memcpy(snapshot, remote->users, count * sizeof(UserData));
        pthread_mutex_unlock(&remote->mutex);

        SDL_SetRenderDrawColor(app->render, 0, 255, 0, 255); 
        for (int i = 0; i < count; i++) {
            SDL_Rect r = { snapshot[i].x, snapshot[i].y, USER_DEFAULT_WIDTH, USER_DEFAULT_HEIGHT };
            SDL_RenderFillRect(app->render, &r);
        }

        SDL_RenderPresent(app->render);
    }
}