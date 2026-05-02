#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include <bullet.h>
#include <painter.h>
#include <map.h>
#include <camera.h>
#include <common.h>
#include <SDL3/SDL_mouse.h>

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
 * Draw the player's eye sight
 */
void Player_DrawSight(SDL_Renderer *renderer, Player *player, Map *map);

/**
 * Update player's actions
 */
void Player_Update(Player *player, Uint64 deltaTime, BulletList *bulletList, Map *map);

/**
 * Delete a player
 */
void Player_Delete(Player *player);

#endif /* INCLUDE_PLAYER_H */