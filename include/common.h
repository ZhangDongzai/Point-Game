#ifndef POINT_GAME_INCLUDE_COMMON_H_
#define POINT_GAME_INCLUDE_COMMON_H_

#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define HANDLE_ERROR(msg) fprintf(stderr, msg ": %s\n", SDL_GetError()); \
    exit(EXIT_FAILURE)

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    const Uint8 *keyboard_state;
    float delta_time_s;
} App;

extern App app;

#endif // POINT_GAME_INCLUDE_COMMON_H_
