#include <draw.h>


void drawFillCircle(SDL_Renderer *renderer, int radius, int x, int y) {
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if (dx*dx + dy*dy <= radius * radius)
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}
