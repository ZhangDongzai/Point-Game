#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include <common.h>

#define PLAYER_DEFAULT_DIRECTION 0
#define PLAYER_DEFAULT_POS (int[]) {5, 5}
#define PLAYER_SIZE 10

/**
 * The struct used as an opaque handle to a player
 * 
 * \sa Player_Create 
 */
typedef struct 
{
    int pos[2];         /* Player's position */
    float direction;
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
 * Get the player's direction
 * 
 * \param player the player context
 * 
 * \returns a float number between 0 and 2 pie
 * 
 * \sa Player_Create
 */
float Player_GetDirection(Player *player);

/**
 * Delete the player
 * 
 * \param player the player context
 * 
 * \sa Player_Create
 */
void Player_Delete(Player *player);

#endif /* INCLUDE_PLAYER_H */