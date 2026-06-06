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
	/* Eye sight */
	float direction;
	SDL_Texture *sightTexture;

	/* Magazine */
	BulletMagazine magazine;

	/* Render object */
	Render_Object object;

	/* Texture */
	Uint64 prevChangeTextureTime;
	Uint8 textureNumber;
	SDL_Texture *textures[PLAYER_TEXTURE_NUMBER];
} Player;

/**
 * Create a player
 * 
 * \returns the player struct context
 */
Player Player_Create(SDL_Renderer *renderer, BulletList *bulletList);

/**
 * Draw the player's eye sight
 */
void Player_DrawSight(SDL_Renderer *renderer, Player *player, Map *map);

/**
 * Update player's actions
 */
void Player_Update(Player *player, Uint64 deltaTime, BulletList *bulletList,
		   Map *map, bool *isMouseUsable);

/**
 * Delete a player
 */
void Player_Delete(Player *player);

#endif /* INCLUDE_PLAYER_H */