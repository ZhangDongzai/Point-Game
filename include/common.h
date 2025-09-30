#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>

// Window
#define WINDOW_NAME "Point Game"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_MAX_FPS 60.0
#define WINDOW_DELTA_TIME (1000 / WINDOW_MAX_FPS)
#define WINDOW_SCALE 100.0f
#define WINDOW_WIDTH_SCALE (WINDOW_WIDTH / WINDOW_SCALE)
#define WINDOW_HEIGHT_SCALE (WINDOW_HEIGHT / WINDOW_SCALE)

// Player
#define PLAYER_DEFAULT_DIRECTION 0
#define PLAYER_DEFAULT_POS (float[]) {6, 3}
#define PLAYER_SIZE 1
#define PLAYER_COLOR (SDL_Color) {255, 255, 255, 255}
#define PLAYER_SHAPE RENDER_SHAPE_CIRCLE
#define PLAYER_MOVE_SPEED 2     // pixel/s
#define PLAYER_TURN_SPEED 2     // rad/s

// Map
#define MAP_WIDTH 15
#define MAP_HEIGHT 10
#define MAP_COLOR_WALL (SDL_Color) {255, 255, 255, 255}
#define MAP_COLOR_AIR (SDL_Color) {0, 0, 0, 0}

#endif /* INCLUDE_COMMON_H */