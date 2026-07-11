#ifndef USER_H
#define USER_H

#include "window.h"

#define USER_DEFAULT_POS_X 0
#define USER_DEFAULT_POS_Y 0
#define USER_DEFAULT_WIDTH 100
#define USER_DEFAULT_HEIGHT 100

typedef struct {
    int x;
    int y;
    SDL_Rect user_rect;
    SDL_Color color;
    SDL_Texture *texture;
}User;

bool InitUser(User *user, Window *app);

bool DrawUser(SDL_Renderer *render, User *user);

void MoveUser(User *user, int x, int y);

#endif