#ifndef INCLUDE_BULLET_H
#define INCLUDE_BULLET_H

#include <enemy.h>
#include <map.h>
#include <camera.h>
#include <common.h>

/**
 * The bullet context
 */
typedef Render_Object Bullet;

/**
 * Magazine status
 */
typedef struct {
	SDL_Texture *texture;
	struct list_head *bulletList;
	short bulletNumber;
	Uint64 prevReloadTime;
	Uint64 prevShootTime;
} BulletMagazine;

/**
 * Init a bullet list
 */
void Bullet_Init(struct list_head *bulletList);

/**
 * Create a bullet and shoot
 *
 * \return true if the bullet is created successfully, otherwise false
 */
bool Bullet_Create(BulletMagazine *magazine, SDL_FPoint *pos, float direction);

/**
 * Reload magazine
 */
void Bullet_ReloadMagazine(BulletMagazine *magazine);

/**
 * Update the position of bullet
 */
void Bullet_UpdateList(struct list_head *bulletList, Uint64 deltaTime, Map *map,
		       Enemys *enemys);

/** 
 * Delete a bullet list
 */
void Bullet_DeleteList(struct list_head *bulletList);

#endif /* INCLUDE_BULLET_H */