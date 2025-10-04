#include <bullet.h>


BulletList* Bullet_CreateList() {
    return (BulletList *)calloc(1, sizeof(BulletList));
}

void Bullet_Create(Render_Object *object, BulletList *bulletList) {
    for (; bulletList->object; bulletList = bulletList->next) {
        if (!bulletList->next) {
            bulletList->next = Bullet_CreateList();
        }
    }

    Bullet* bullet = (Bullet *)calloc(1, sizeof(Bullet));
    bullet->rect.x = object->rect.x;
    bullet->rect.y = object->rect.y;
    bullet->rect.w = BULLET_WIDTH;
    bullet->rect.h = BULLET_HEIGHT;
    bullet->direction = object->direction;
    bullet->color = BULLET_COLOR;
    bullet->shape = BULLET_SHAPE;

    bulletList->object = bullet;
}

void Bullet_UpdateList(BulletList **bulletList, Uint64 deltaTime) {
    for (BulletList *list = *bulletList; list != NULL; list = list->next) {
        if (!list->object) continue;
        
        list->object->rect.x += BULLET_SPEED * deltaTime / 1000.0f * SDL_cosf(list->object->direction);
        list->object->rect.y += BULLET_SPEED * deltaTime / 1000.0f * SDL_sinf(list->object->direction);

        if (Map_IsHit(list->object->rect.x, list->object->rect.y)) {
            Bullet_Delete(list->object);
            list->object = NULL;
        }
    }

    for (BulletList *list = *bulletList; list->next != NULL; list = list->next) {
        if (list->object) continue;
        BulletList *nextList = list->next;
        if (!nextList->next) break;
        list->next = nextList->next;
        free(nextList);
    }
}

void Bullet_Delete(Bullet *bullet) {
    free(bullet);
}