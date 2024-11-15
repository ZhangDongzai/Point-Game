#ifndef POINT_GAME_INCLUDE_COMMON_H
#define POINT_GAME_INCLUDE_COMMON_H

#include <SDL2/SDL.h>

#define COS_45 0.7071
#define SIN_45 COS_45

#define WINDOW_NAME "Point Game"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_FPS 60

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    const Uint8 *keyBoardState;
} App;

extern App app;

#endif // POINT_GAME_INCLUDE_COMMON_H
