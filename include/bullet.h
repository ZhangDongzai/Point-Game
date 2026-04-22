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
 * Create a bullet
 * 
 * \param magazine the player's magazine
 * \param object the player's render object
 *
 * \return true if the bullet is created successfully, otherwise false
 */
bool Bullet_Create(BulletMagazine *magazine, Render_Object *object);

/**
 * Reload magazine
 *
 * \param magazine the player's magazine
 */
void Bullet_ReloadMagazine(BulletMagazine *magazine);

/**
 * Update the position of bullet
 * 
 * \param bullets the list of bullet contexts
 * \param deltaTime the delta time between frames
 */
void Bullet_UpdateList(BulletList *bullets, Uint64 deltaTime);

/**
 * Delete the bullet
 * 
 * \param bullet tthe bullet context
 */
void Bullet_Delete(Bullet *bullet);

#endif /* INCLUDE_BULLET_H */