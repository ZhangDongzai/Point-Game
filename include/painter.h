#ifndef INCLUDE_PAINTER_H
#define INCLUDE_PAINTER_H

#include <camera.h>
#include <common.h>

/**
 * Draw a circle
 */
void Painter_DrawCircle(SDL_Renderer *renderer, float centerX, float centerY,
			float radius, SDL_Color color, bool isSolid);

#endif /* INCLUDE_PAINTER_H */