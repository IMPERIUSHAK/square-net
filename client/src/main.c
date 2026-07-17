#include "window.h"
#include "user.h"
#include "loop.h"
#include "pthread.h"
#include "net_client.h"
int main(){

    pthread_t keyhandler_thread;
    pthread_t server_thread;

    pthread_mutex_t isRunningMutex;
    pthread_mutex_t userMutex;
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
    
    pthread_mutex_init(&isRunningMutex, NULL);
    pthread_mutex_init(&userMutex, NULL);
    
    EventThreadArgs args = {.isRunning = &isRunning, .screen = &screen, .user = &user, .isRunningMutex = &isRunningMutex, .userMutex = &userMutex};
    
    NetClient clientargs = {0};
    
    ConnectionThreadArgs conthargs= {.isRunning = &isRunning, .netclient = &clientargs, .isRunningMutex = &isRunningMutex, .user = &user, .userMutex = &userMutex};

    pthread_create(&keyhandler_thread, NULL, handle_events, &args);
    pthread_create(&server_thread, NULL, handle_connection, &conthargs);
    
    run_loop(&screen, &user, &isRunning, &isRunningMutex);
    
    pthread_join(keyhandler_thread, NULL);
    pthread_join(server_thread, NULL);

    pthread_mutex_destroy(&isRunningMutex);
    pthread_mutex_destroy(&userMutex);
    SDL_DestroyTexture(user.texture);
    SDL_DestroyRenderer(screen.render);
}