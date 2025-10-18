#include <bullet.h>


BulletList* Bullet_CreateList() {
    return (BulletList *)calloc(1, sizeof(BulletList));
}

void Bullet_Create(Render_Object *object, BulletList *bulletList) {
    for (; bulletList->object; bulletList = bulletList->next) {
        if (!bulletList->next) {
            bulletList->next = Bullet_CreateList();
            bulletList->next->prev = bulletList;
        }
    }

    Bullet* bullet = (Bullet *)calloc(1, sizeof(Bullet));
    bullet->rect.x = object->rect.x + object->rect.w / 2.0f - BULLET_WIDTH / 2.0f;
    bullet->rect.y = object->rect.y + object->rect.h / 2.0f - BULLET_HEIGHT / 2.0f;
    bullet->rect.w = BULLET_WIDTH;
    bullet->rect.h = BULLET_HEIGHT;
    bullet->direction = object->direction;

    SDL_Surface *surface = SDL_CreateSurface(MAP_WIDTH, MAP_HEIGHT, SDL_PIXELFORMAT_RGBA32);
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);

    SDL_SetRenderDrawColor(renderer, BULLET_COLOR.r, BULLET_COLOR.g, BULLET_COLOR.b, BULLET_COLOR.a);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    bullet->texture = Camera_CreateTextureFromSurface(surface);

    bulletList->object = bullet;
}

void Bullet_UpdateList(BulletList *bulletList, Uint64 deltaTime) {
    for (; bulletList; bulletList = bulletList->next) {
        if (!bulletList->object) continue;

        bulletList->object->rect.x += SDL_cosf(bulletList->object->direction) 
                                        * BULLET_SPEED * deltaTime / 1000.0f;
        bulletList->object->rect.y += SDL_sinf(bulletList->object->direction) 
                                        * BULLET_SPEED * deltaTime / 1000.0f;
        
        if (!Map_IsHit(bulletList->object->rect.x, bulletList->object->rect.y)) {
            continue;
        }

        Bullet_Delete(bulletList->object);
        bulletList->object = NULL;

        if (bulletList->prev && bulletList->next) {
            bulletList->prev->next = bulletList->next;
            bulletList->next->prev = bulletList->prev;
        }
    }
}

void Bullet_Delete(Bullet *bullet) {
    free(bullet);
}