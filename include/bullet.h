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
 * Create a list of bullets
 */
BulletList* Bullet_CreateList();

/**
 * Create a bullet
 * 
 * \param object the bullet's shooter
 * \param bullets the list of bullets
 */
void Bullet_Create(Render_Object *object, BulletList *bullets);

/**
 * Update the position of bullet
 * 
 * \param bullets the list of bullet contexts
 * \param deltaTime the delta time between frames
 */
void Bullet_UpdateList(BulletList **bullets, Uint64 deltaTime);

/**
 * Delete the bullet
 * 
 * \param bullet tthe bullet context
 */
void Bullet_Delete(Bullet *bullet);

#endif /* INCLUDE_BULLET_H */