#ifndef INCLUDE_PAINTER_H
#define INCLUDE_PAINTER_H

#include <camera.h>
#include <common.h>

/**
 * Draw a circle
 *
 * \param radius the radius of the circle
 * \param color the color of the circle
 * \param isSolid whether the circle is solid
 *
 * \returns a SDL_Texture pointer
 */
SDL_Texture *Painter_DrawCircle(float radius, SDL_Color color, bool isSolid);

#endif /* INCLUDE_PAINTER_H */