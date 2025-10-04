#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include <bullet.h>
#include <map.h>
#include <camera.h>
#include <common.h>

/**
 * The player conext
 */
typedef Render_Object Player;

/**
 * Create a player
 * 
 * \returns the player struct context
 * 
 * \sa Player_Delete
 */
Player* Player_Create();

/**
 * Check keyboard and update player's position
 * 
 * \param player the player context
 * 
 * \sa Player_Create
 */
void Player_Update(Player *player, Uint64 deltaTime, BulletList *bulletList);

/**
 * Delete the player
 * 
 * \param player the player context
 * 
 * \sa Player_Create
 */
void Player_Delete(Player *player);

#endif /* INCLUDE_PLAYER_H */