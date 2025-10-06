#include <camera.h>

static Camera camera;

void Camera_BindRenderer(SDL_Renderer *renderer, float *pos) {
    camera.renderer = renderer;
    memcpy(camera.pos, pos, sizeof(camera.pos));
}

void Camera_RenderObject(Render_Object *object) {
    SDL_SetRenderDrawColor(camera.renderer, object->color.r,
        object->color.g, object->color.b, object->color.a);

    float objectX = (object->rect.x - camera.pos[0]) * WINDOW_SCALE + WINDOW_WIDTH / 2.0f;
    float objectY = (object->rect.y - camera.pos[1]) * WINDOW_SCALE + WINDOW_HEIGHT / 2.0f;

    switch (object->shape) {
    case RENDER_SHAPE_RECT:
        SDL_FRect rect = {objectX - (object->rect.w / 2.0f) * WINDOW_SCALE,
            objectY - (object->rect.h / 2.0f) * WINDOW_SCALE,
            object->rect.w * WINDOW_SCALE, object->rect.h * WINDOW_SCALE};
        SDL_RenderFillRect(camera.renderer, &rect);
        break;
    case RENDER_SHAPE_CIRCLE:
        const float radius = object->rect.w * WINDOW_SCALE / 2.0f;
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
            } else {
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

void Camera_RenderObjects(Render_ObjectNode *objectNode) {
    for (Render_ObjectNode *node = objectNode; node != NULL; node = node->next) {
        if (!node->object) continue;
        Camera_RenderObject(node->object);
    }
}

void Camera_Update(Render_Object *object, Render_Boundary *boundary) {
    camera.pos[0] = object->rect.x;
    camera.pos[1] = object->rect.y;

    float left = boundary->left + WINDOW_WIDTH_SCALE / 2.0f;
    float right = boundary->right - WINDOW_WIDTH_SCALE / 2.0f;
    float up = boundary->up + WINDOW_HEIGHT_SCALE / 2.0f;
    float down = boundary->down - WINDOW_HEIGHT_SCALE / 2.0f;
    
    if (object->rect.x < left) {
        camera.pos[0] = left;
    } else if (object->rect.x > right) {
        camera.pos[0] = right;
    } if (object->rect.y < up) {
        camera.pos[1] = up;
    } else if (object->rect.y > down) {
        camera.pos[1] = down;
    }
}