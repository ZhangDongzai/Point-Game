#ifndef INCLUDE_MAIN_H
#define INCLUDE_MAIN_H

#define SDL_MAIN_USE_CALLBACKS

#include <camera.h>
#include <player.h>
#include <common.h>
#include <SDL3/SDL_main.h>

// Window info
#define WINDOW_NAME "Point Game"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_MAX_FPS 60.0
#define WINDOW_DELTA_TIME (1000 / WINDOW_MAX_FPS)

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Player *player;
    Uint64 preFrameTime;
    Uint64 deltaTime;
} App;

#endif /* INCLUDE_MAIN_H */
