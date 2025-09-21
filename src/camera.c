#include <camera.h>

static SDL_Renderer *Camera_Renderer = NULL;

void Camera_BindRenderer(SDL_Renderer *renderer) {
    Camera_Renderer = renderer;
}

void Camera_RenderObject(Render_Object *object) {
    SDL_SetRenderDrawColor(Camera_Renderer, object->color.r,
        object->color.g, object->color.b, object->color.a);
    switch (object->shape) {
    case RENDER_SHAPE_RECTANGLE:
        SDL_FRect rect;
        rect.x = object->pos[0] - 0.5 * object->size;
        rect.y = object->pos[1] - 0.5 * object->size;
        rect.w = object->size;
        rect.h = object->size;
        SDL_RenderRect(Camera_Renderer, &rect);
        break;
    case RENDER_SHAPE_CIRCLE:
        const float radius = object->size * 0.5;
        const float diameter = radius * 2;

        float x = (radius - 1);
        float y = 0;
        float tx = 1;
        float ty = 1;
        float error = (tx - diameter);

        while (x >= y) {
            SDL_RenderPoint(Camera_Renderer, object->pos[0] + x, object->pos[1] - y);
            SDL_RenderPoint(Camera_Renderer, object->pos[0] + x, object->pos[1] + y);
            SDL_RenderPoint(Camera_Renderer, object->pos[0] - x, object->pos[1] - y);
            SDL_RenderPoint(Camera_Renderer, object->pos[0] - x, object->pos[1] + y);
            SDL_RenderPoint(Camera_Renderer, object->pos[0] + y, object->pos[1] - x);
            SDL_RenderPoint(Camera_Renderer, object->pos[0] + y, object->pos[1] + x);
            SDL_RenderPoint(Camera_Renderer, object->pos[0] - y, object->pos[1] - x);
            SDL_RenderPoint(Camera_Renderer, object->pos[0] - y, object->pos[1] + x);

            if (error <= 0) {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0) {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }

        SDL_RenderLine(Camera_Renderer, object->pos[0], object->pos[1],
            object->pos[0] + SDL_cosf(object->direction) * 100,
            object->pos[1] + SDL_sinf(object->direction) * 100);
        break;
    }
}