#ifndef INCLUDE_BULLET_H
#define INCLUDE_BULLET_H

#include <map.h>
#include <camera.h>
#include <common.h>

/**
 * The bullet context
 */
typedef Render_Object Bullet;

/**
 * A list of bullets
 */
typedef Render_ObjectNode BulletList;

/**
 * Magazine status
 */
typedef struct {
	SDL_Texture *bullet;
	BulletList *bulletList;
	short bulletNumber;
	Uint64 prevReloadTime;
	Uint64 prevShootTime;
} BulletMagazine;

/**
 * Create a list of bullets
 */
BulletList *Bullet_CreateList();

/**
 * Create a bullet and shoot
 *
 * \return true if the bullet is created successfully, otherwise false
 */
bool Bullet_Create(BulletMagazine *magazine, Render_Object *object,
		   float direction);

/**
 * Reload magazine
 */
void Bullet_ReloadMagazine(BulletMagazine *magazine);

/**
 * Update the position of bullet
 */
void Bullet_UpdateList(BulletList *bullets, Uint64 deltaTime, Map *map);

/** 
 * Delete a bullet list
 */
void Bullet_DeleteList(BulletList *bulletList);

#endif /* INCLUDE_BULLET_H */