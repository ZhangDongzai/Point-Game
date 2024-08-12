#ifndef POINT_GAME_INCLUDE_DISPLAY_H_
#define POINT_GAME_INCLUDE_DISPLAY_H_

#include <common.h>

// Base function
void InitDisplay();
void QuitDisplay();

// Draw function
void DrawCircle(SDL_Renderer *renderer, SDL_Point center, int radius, SDL_Color color);

// Colors
#define EMPTY (SDL_Color) {0, 0, 0, 0}
#define WHITE (SDL_Color) {255, 255, 255, 255}
#define BLACK (SDL_Color) {0, 0, 0, 255}

// Window's info
#define WINDOW_TITLE "Point Game"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_BACKGROUND BLACK

#endif // POINT_GAME_INCLUDE_DISPLAY_H_
