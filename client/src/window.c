#include "window.h"

bool CreateWindow(Window *app){

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    app->window = SDL_CreateWindow(app->WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    app->WINDOW_WIDTH, app->WINDOW_HEIGHT, 0);
    
    if (!app->window){
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return false;
    }

    app->render = SDL_CreateRenderer(app->window, -1, 0);

    if (!app->render){
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}