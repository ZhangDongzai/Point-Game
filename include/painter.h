#ifndef INCLUDE_PAINTER_H
#define INCLUDE_PAINTER_H

#include <camera.h>
#include <common.h>

/**
 * Draw a circle
 *
 * \returns a SDL_Texture pointer
 */
SDL_Texture *Painter_DrawCircle(float radius, SDL_Color color, bool isSolid);

/**
 * Draw a dark overlay on the screen
 */
void Painter_DrawDarkOverlay(SDL_Renderer *renderer);

#endif /* INCLUDE_PAINTER_H */