#include "window.h"
#include "user.h"
#include "loop.h"
#include "pthread.h"

int main(){

    pthread_t keyhandler_thread;
    bool isRunning = true;

    Window screen = {.WINDOW_WIDTH = DEFAULT_SCREEN_WIDTH, .WINDOW_HEIGHT = DEFAULT_SCREEN_HEIGHT, 
                        .WINDOW_TITLE = DEFAULT_SCREEN_TITLE};
    
    if (!CreateWindow(&screen)){
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return -1;
    }
    
    User user;
    InitUser(&user, &screen);

    SDL_Event event;
    screen.event = &event;

    SDL_SetRenderDrawBlendMode(screen.render, SDL_BLENDMODE_BLEND);
    

    pthread_mutex_t isRunningMutex;
    pthread_mutex_init(&isRunningMutex, NULL);

    EventThreadArgs args = {.isRunning = &isRunning, .screen = &screen, .user = &user, .isRunningMutex = &isRunningMutex};
    pthread_create(&keyhandler_thread, NULL, handle_events, &args);
    
    run_loop(&screen, &user, &isRunning, &isRunningMutex);
    pthread_join(keyhandler_thread, NULL);
    pthread_mutex_destroy(&isRunningMutex);

    SDL_DestroyTexture(user.texture);
    SDL_DestroyRenderer(screen.render);
}