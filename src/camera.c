#include <window.h>
#include <camera.h>

static Camera camera;

void Camera_BindRenderer(SDL_Renderer *renderer, float *pos) {
    camera.renderer = renderer;
    memcpy(camera.pos, pos, sizeof(camera.pos));
}

void Camera_RenderObject(Render_Object *object) {
    SDL_SetRenderDrawColor(camera.renderer, object->color.r,
        object->color.g, object->color.b, object->color.a);

    float objectX = object->pos[0] - camera.pos[0] + (WINDOW_WIDTH / 2.0f);
    float objectY = object->pos[1] - camera.pos[1] + (WINDOW_HEIGHT / 2.0f);

    switch (object->shape) {
    case RENDER_SHAPE_RECTANGLE:
        SDL_FRect rect = {objectX - (object->size / 2), objectY - (object->size / 2),
            object->size, object->size};
        SDL_RenderRect(camera.renderer, &rect);
        break;
    case RENDER_SHAPE_CIRCLE:
        const float radius = object->size / 2.0f;
        const float diameter = radius * 2.0f;

        float x = radius - 1.0f;
        float y = 0.0f;
        float tx = 1.0f;
        float ty = 1.0f;
        float error = tx - diameter;

        while (x >= y) {
            SDL_RenderPoint(camera.renderer, objectX + x, objectY - y);
            SDL_RenderPoint(camera.renderer, objectX + x, objectY + y);
            SDL_RenderPoint(camera.renderer, objectX - x, objectY - y);
            SDL_RenderPoint(camera.renderer, objectX - x, objectY + y);
            SDL_RenderPoint(camera.renderer, objectX + y, objectY - x);
            SDL_RenderPoint(camera.renderer, objectX + y, objectY + x);
            SDL_RenderPoint(camera.renderer, objectX - y, objectY - x);
            SDL_RenderPoint(camera.renderer, objectX - y, objectY + x);

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

        SDL_RenderLine(camera.renderer, objectX, objectY,
            objectX + SDL_cosf(object->direction) * 100,
            objectY + SDL_sinf(object->direction) * 100);
        break;
    }
}

void Camera_Update(Render_Object *object) {
    memcpy(camera.pos, object->pos, sizeof(camera.pos));
}