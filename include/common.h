#ifndef POINT_GAME_INCLUDE_COMMON_H
#define POINT_GAME_INCLUDE_COMMON_H

<<<<<<< HEAD
#include <math.h>
#include <stdbool.h>
=======
>>>>>>> parent of 6b7b371 (fix: var name)
#include <SDL2/SDL.h>

#define COS_45 0.7071
#define SIN_45 COS_45

#define WINDOW_NAME "Point Game"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_FPS 60

<<<<<<< HEAD
#define PLAYER_RADIUS 25
#define PLAYER_COLOR (SDL_Color) {255, 255, 255, 255}
#define PLAYER_MOVE_SPEED_MS 0.3
#define PLAYER_TURN_SPEED_MS 0.004

#define MAP_PATH "../res/map"
#define MAP_COLUMN 16
#define MAP_ROW 9
#define MAP_WIDTH (WINDOW_WIDTH / MAP_COLUMN)
#define MAP_HEIGHT (WINDOW_HEIGHT / MAP_ROW)
#define MAP_AIR 0
#define MAP_WALL 1
=======
#define MAP_PATH "../res/map"
#define MAP_WIDTH 16
#define MAP_HEIGHT 9
#define MAP_COLOR_BLACK 0
#define MAP_COLOR_WHITE 1
>>>>>>> parent of 6b7b371 (fix: var name)

#define RAY_FOV (M_PI / 3.0f)
#define RAY_NUMBER WINDOW_WIDTH
#define RAY_DELTA_ANGLE (float) (RAY_FOV / (float) RAY_NUMBER)
#define RAY_MAX_DEPTH 20

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    const Uint8 *keyBoardState;
} App;

extern App app;

#endif // POINT_GAME_INCLUDE_COMMON_H
