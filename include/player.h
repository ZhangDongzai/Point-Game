#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include <camera.h>
#include <common.h>

#define PLAYER_DEFAULT_DIRECTION 0
#define PLAYER_DEFAULT_POS (float[]) {640, 360}
#define PLAYER_SIZE 100
#define PLAYER_COLOR (SDL_Color) {255, 255, 255, 255}
#define PLAYER_SHAPE RENDER_SHAPE_CIRCLE

/**
 * The struct used as an opaque handle to a player
 * 
 * \sa Player_Create 
 */
typedef struct 
{
    float pos[2];         // The player's position
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
float* Player_GetPos(Player *player);

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
 * Get a render context for camera.
 * If the function has been ran, it will return the same ptr.
 * 
 * \param player the player context
 * 
 * \returns a render context
 * 
 * \sa Player_Create
 */
Render_Object* Player_GetRenderObject(Player *player);

/**
 * Delete the player
 * 
 * \param player the player context
 * 
 * \sa Player_Create
 */
void Player_Delete(Player *player);

#endif /* INCLUDE_PLAYER_H */