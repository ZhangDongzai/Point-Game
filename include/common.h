#ifndef POINT_GAME_INCLUDE_COMMON_H
#define POINT_GAME_INCLUDE_COMMON_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define COS_45 0.7071
#define SIN_45 COS_45

#define WINDOW_NAME "Point Game"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_FPS 60

#define PLAYER_RADIUS 25
#define PLAYER_COLOR (SDL_Color) {255, 255, 255, 255}
#define PLAYER_MOVE_SPEED_MS 0.3
#define PLAYER_TURN_SPEED_MS 0.003

#define MAP_PATH "../res/map"
#define MAP_WIDTH 16
#define MAP_HEIGHT 9
#define MAP_AIR 0
#define MAP_WALL 1

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    const Uint8 *keyBoardState;
} App;

extern App app;

#endif // POINT_GAME_INCLUDE_COMMON_H
