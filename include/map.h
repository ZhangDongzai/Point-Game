#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

#include <camera.h>
#include <common.h>

#define MAP_WIDTH 15
#define MAP_HEIGHT 10
#define MAP_SIZE 100
#define MAP_COLOR_WALL (SDL_Color) {255, 255, 255, 255}
#define MAP_COLOR_AIR (SDL_Color) {0, 0, 0, 0}

extern int map[MAP_HEIGHT][MAP_WIDTH];

/**
 * Get a node of render objects
 * 
 * \sa Render_ObjectNode
 */
Render_ObjectNode* Map_GetObjects();

/**
 * Get the boundary of a map
 * 
 * \sa Map_Boundary
 */
Render_Boundary *Map_GetBoundary();

/**
 * Free memory of the map
 * 
 * \param objectNode the node of map
 * 
 * \sa Map_GetObjects
 */
void Map_Delete(Render_ObjectNode *objectNode);

#endif /* INCLUDE_MAP_H */