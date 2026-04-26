#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>

// Window
#define WINDOW_NAME "Point Game"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_MAX_FPS 60.0f
#define WINDOW_DELTA_TIME (1000 / WINDOW_MAX_FPS)
#define WINDOW_SCALE 100.0f
#define WINDOW_WIDTH_SCALE (WINDOW_WIDTH / WINDOW_SCALE)
#define WINDOW_HEIGHT_SCALE (WINDOW_HEIGHT / WINDOW_SCALE)

// Player
#define PLAYER_DEFAULT_DIRECTION 0.0f
#define PLAYER_DEFAULT_POS (float[]){ 6.0f, 4.0f }
#define PLAYER_SIZE 0.5f
#define PLAYER_COLOR (SDL_Color){ 0, 255, 0, 255 }
#define PLAYER_SHAPE RENDER_SHAPE_CIRCLE
#define PLAYER_MOVE_SPEED 3.0f
#define PLAYER_TURN_SPEED 3.0f

// Map
#define MAP_WIDTH 15
#define MAP_HEIGHT 10
#define MAP_CODE_WALL 1
#define MAP_CODE_FLOOR 0
#define MAP_COLOR_WALL (SDL_Color){ 255, 255, 255, 255 }
#define MAP_COLOR_FLOOR (SDL_Color){ 169, 169, 169, 255 }

// Bullet
#define BULLET_WIDTH 0.2f
#define BULLET_HEIGHT 0.08f
#define BULLET_COLOR (SDL_Color){ 255, 255, 0, 255 }
#define BULLET_SHAPE RENDER_SHAPE_RECT
#define BULLET_SPEED 10.0f
#define BULLET_SHOOT_DELTA 100.0f
#define BULLET_MAX_COUNT 30
#define BULLET_RELOAD_TIME_MS 1000.0f

// Info label
#define INFOLABEL_COLOR (SDL_Color){ 255, 255, 255, 255 }
#define INFOLABEL_FONT "./sources/fusion-pixel-10px-monospaced-zh_hans.ttf"
#define INFOLABEL_FONT_SIZE WINDOW_SCALE * 0.8f

#endif /* INCLUDE_COMMON_H */