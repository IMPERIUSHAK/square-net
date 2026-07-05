#include "window.h"

bool CreateWindow(Window *window){

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    window->window = SDL_CreateWindow(window->WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    window->WINDOW_WIDTH, window->WINDOW_HEIGHT, 0);
    
    if (!window->window){
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return false;
    }

    window->render = SDL_CreateRenderer(window->window, -1, 0);

    if (!window->render){
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}