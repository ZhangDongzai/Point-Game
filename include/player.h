#ifndef POINT_GAME_INCLUDE_PLAYER_H
#define POINT_GAME_INCLUDE_PLAYER_H

#include <math.h>
#include <stdio.h>
#include <common.h>
#include <draw.h>

#define PLAYER_RADUIS 50
#define PLAYER_COLOR (SDL_Color) {255, 255, 255, 255}
#define PLAYER_SPEED_MS 0.2

typedef struct {
    int x, y;
    float fx, fy;
    float direction;
    SDL_Color color;
} Player;

Player* createPlayer(int x, int y, SDL_Color color);
void updatePlayer(Player *player, unsigned int deltaTimeMs);
void renderPlayer(SDL_Renderer *renderer, Player *player);
void destroyPlayer(Player *player);

#endif // POINT_GAME_INCLUDE_PLAYER_H
