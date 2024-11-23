#ifndef POINT_GAME_INCLUDE_MAP_H
#define POINT_GAME_INCLUDE_MAP_H

#include <common.h>
#include <stdio.h>

typedef int** Map;

Map loadMap();
void renderMap(SDL_Renderer *renderer, Map map);

#endif // POINT_GAME_INCLUDE_MAP_H