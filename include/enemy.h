#ifndef INCLUDE_ENEMY_H
#define INCLUDE_ENEMY_H

#include <common.h>
#include <camera.h>

typedef Render_Object Enemy;

typedef struct {
	SDL_Texture *texture[ENEMY_TEXTURE_ROWS][ENEMY_TEXTURE_COLUMNS];
	struct list_head *list;
} Enemys;

Enemys Enemy_Init();

void Enemy_Create(Enemys *enemys, const SDL_FPoint *pos);

bool Enemy_IsHit(Enemys *enemys, const SDL_FPoint *pos);

void Enemy_Delete(Enemys *enemys);

void Enemy_Update(Enemys *enemys);

#endif /* INCLUDE_ENEMY_H */