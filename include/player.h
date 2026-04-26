#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include <bullet.h>
#include <painter.h>
#include <map.h>
#include <camera.h>
#include <common.h>

/**
 * The player context
 */
typedef struct {
	BulletMagazine magazine;
	Render_Object *object;
} Player;

/**
 * Create a player
 * 
 * \returns the player struct context
 */
Player *Player_Create(BulletList *bulletList);

/**
 * Draw the player's sight
 * 
 * \param renderer the renderer context
 * \param player the player context
 */
void Player_DrawSight(SDL_Renderer *renderer, Player *player);

/**
 * Check keyboard and update player's position
 * 
 * \param player the player context
 */
void Player_Update(Player *player, Uint64 deltaTime, BulletList *bulletList);

/**
 * Delete the player
 * 
 * \param player the player context
 */
void Player_Delete(Player *player);

#endif /* INCLUDE_PLAYER_H */