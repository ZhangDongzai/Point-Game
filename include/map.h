#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

#include <camera.h>
#include <common.h>

extern int mapList[MAP_HEIGHT][MAP_WIDTH];

typedef Render_Object Map;

/**
 * Get a renderable object of map
 * 
 * \returns the map context
 */
Map *Map_Create();

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
 * Free memory of the map
 * 
 * \param map the map context
 */
void Map_Delete(Map *map);

#endif /* INCLUDE_MAP_H */