#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

#include <camera.h>
#include <common.h>

typedef enum {
	MAP_CODE_FLOOR,
	MAP_CODE_WALL,
	MAP_CODE_WALL_LIGHT,
} MAP_CODE;

extern int mapList[MAP_HEIGHT][MAP_WIDTH];

typedef Render_Object Map;

/**
 * Get a renderable object of map
 * 
 * \returns the map context
 */
Map *Map_Create();

/**
 * Clean up light walls on the map
 */
void Map_Clean();

/**
 * Get the boundary of a map
 * 
 * \returns the render boundary context
 */
Render_Boundary *Map_GetBoundary();

/**
 * Tell the object if it hits walls
 * 
 * \param x the object's pos x
 * \param y the object's pos y
 * 
 * \returns a bool value
 */
bool Map_IsHit(float x, float y);

/**
 * Update the map
 * 
 * \param map the map context
 */
void Map_Update(Map *map);

/**
 * Set the light wall
 * 
 * \param x the wall's pos x
 * \param y the wall's pos y
 */
void Map_SetLightWall(float x, float y);

/**
 * Free memory of the map
 * 
 * \param map the map context
 */
void Map_Delete(Map *map);

#endif /* INCLUDE_MAP_H */