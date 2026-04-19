#ifndef INCLUDE_PAINTER_H
#define INCLUDE_PAINTER_H

#include <camera.h>
#include <common.h>

/**
 * Draw a hollow circle
 *
 * \returns a SDL_Texture pointer
 */
SDL_Texture* Painter_DrawHollowCircle(float radius, SDL_Color color);

#endif /* INCLUDE_PAINTER_H */