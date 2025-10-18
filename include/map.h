#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

#include <camera.h>
#include <common.h>

extern int mapList[MAP_HEIGHT][MAP_WIDTH];

typedef Render_Object Map;

/**
 * Get a node of render objects
 * 
 * \returns the render objects context
 * 
 * \sa Render_ObjectNode
 */
Map* Map_Create();

/**
 * Get the boundary of a map
 * 
 * \returns the render boundary context
 * 
 * \sa Map_Boundary
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
 * \param objectNode the node of map
 * 
 * \sa Map_GetObjects
 */
void Map_Delete(Render_ObjectNode *objectNode);

#endif /* INCLUDE_MAP_H */