#include "user.h"

bool InitUser(User *user, Window *app){

    user->user_rect.h = USER_DEFAULT_HEIGHT;
    user->user_rect.w = USER_DEFAULT_WIDTH;
    user->user_rect.x = USER_DEFAULT_POS_X;
    user->user_rect.y = USER_DEFAULT_POS_Y;

    user->color.a = 0;
    user->color.b = 0;
    user->color.g = 0;
    user->color.r = 255;

    SDL_Surface *surface = SDL_CreateRGBSurface(0, USER_DEFAULT_WIDTH, USER_DEFAULT_HEIGHT, 32, 0, 0, 0, 0);
    if ( !surface ) return false;
    
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, user->color.r, user->color.g, user->color.b));

    user->texture = SDL_CreateTextureFromSurface(app->render, surface);
    if ( !user->texture ) return false;
    
    SDL_FreeSurface(surface);
    
    return true;

}

bool DrawUser(SDL_Renderer *render, User *user){

    SDL_RenderCopy(render, user->texture, NULL, &user->user_rect);

    return true;
}

void MoveUser(User *user, int x, int y){

    user->user_rect.x += x;
    user->user_rect.y += y;
}