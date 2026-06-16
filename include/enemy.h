#ifndef INCLUDE_ENEMY_H
#define INCLUDE_ENEMY_H

#include <common.h>
#include <camera.h>

typedef Render_ObjectNode Enemy;

typedef struct {
        SDL_Texture *texture;
        Enemy *enemy;
} EnemyHead;

EnemyHead Enemy_Init(SDL_Renderer *renderer);

void Enemy_Create(EnemyHead *enemys, const SDL_FPoint *pos);

bool Enemy_IsHit(EnemyHead *enemys, const SDL_FPoint *pos);

void Enemy_Delete(EnemyHead *enemys);

#endif /* INCLUDE_ENEMY_H */