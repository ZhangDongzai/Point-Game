#ifndef POINT_GAME_INCLUDE_PLAYER_H_
#define POINT_GAME_INCLUDE_PLAYER_H_

#include <common.h>
#include <display.h>


typedef struct {
    SDL_Color color;
    int radius;
    SDL_Point center;
} PlayerBasic;

extern PlayerBasic playerBasic;

typedef struct {
    SDL_Texture *texture;
    SDL_Rect *rect;
    PlayerBasic *playerBasic;
} Player;

Player* create_player();
void destroy_player(Player *player);

#endif // POINT_GAME_INCLUDE_PLAYER_H_