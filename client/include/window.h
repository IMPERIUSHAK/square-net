#include "stdlib.h"
#include "SDL2/SDL.h"
#include "stdbool.h"

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480
#define DEFAULT_SCREEN_TITLE "FREDY"

typedef struct{

    int WINDOW_HEIGHT;
    int WINDOW_WIDTH;
    char *WINDOW_TITLE;
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Event *event;

}Window;

bool CreateWindow(Window *window);