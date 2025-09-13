#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include <common.h>


/**
 * The struct used as an opaque handle to a player
 * 
 * \sa Player_Create 
 */
typedef struct 
{
    int pos[2];         /* Player's position */
    int direction;
} Player;

/**
 * Create a player
 * 
 * \returns the player struct context
 * 
 * \sa Player_Delete
 */
Player* Player_Create();

/**
 * Get the player's position
 * 
 * \param player the player context
 * 
 * \returns a {x, y} array
 * 
 * \sa Player_Create
 */
int* Player_GetPos(Player *player);

/**
 * Delete the player
 * 
 * \param player the player context
 * 
 * \sa Player_Create
 */
void Player_Delete(Player *player);

#endif /* INCLUDE_PLAYER_H */