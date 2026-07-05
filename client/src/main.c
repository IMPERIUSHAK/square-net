#include "window.h"
#include "User.h"
#include "loop.h"

int main(){


    Window screen = {.WINDOW_WIDTH = DEFAULT_SCREEN_WIDTH, .WINDOW_HEIGHT = DEFAULT_SCREEN_HEIGHT, 
                        .WINDOW_TITLE = DEFAULT_SCREEN_TITLE};
    
    if (!CreateWindow(&screen)){
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Event event;
    screen.event = &event;

    SDL_SetRenderDrawBlendMode(screen.render, SDL_BLENDMODE_BLEND);

    run_loop(&screen);
    
}