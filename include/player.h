#ifndef POINT_GAME_INCLUDE_PLAYER_H_
#define POINT_GAME_INCLUDE_PLAYER_H_

#include <common.h>
#include <display.h>


typedef struct {
    SDL_Color color;
    int radius;
    SDL_Point center;
    int speed_s;
} PlayerBasic;

extern PlayerBasic playerBasic;

typedef struct {
    SDL_Texture *texture;
    SDL_FRect *f_rect;
    SDL_Rect *rect;
    PlayerBasic *playerBasic;
} Player;

Player* CreatePlayer();
void DestroyPlayer(Player *player);
void UpdatePlayer(Player *player);

#endif // POINT_GAME_INCLUDE_PLAYER_H_