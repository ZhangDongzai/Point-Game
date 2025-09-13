#ifndef INCLUDE_MAIN_H
#define INCLUDE_MAIN_H

#define SDL_MAIN_USE_CALLBACKS

#include <common.h>
#include <SDL3/SDL_main.h>

// Window info
#define WINDOW_NAME "Point Game"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} app;

#endif /* INCLUDE_MAIN_H */
