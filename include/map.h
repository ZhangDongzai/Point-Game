#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

#include <camera.h>
#include <common.h>

extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern int MAP_MAX_LENGTH;
extern SDL_FPoint MAP_DEFAULT_POS;

typedef enum {
	MAP_CODE_FLOOR,
	MAP_CODE_WALL,
	MAP_CODE_WATER,
	MAP_CODE_GRASS,
} MAP_CODE;

typedef struct {
	int *list;
	SDL_Surface *surface;
	SDL_Renderer *renderer;
	Render_Object object;
} Map;

/**
 * Init map from file
 *
 * \returns the map context
 */
Map Map_Init();

/**
 * Get the boundary of a map
 *
 * \returns the render boundary context
 */
Render_Boundary Map_GetBoundary();

/**
 * Tell the object if it hits walls
 *
 * \returns a bool value
 */
bool Map_IsHit(Map *map, float x, float y);

/**
 * Update the map
 */
void Map_Update(Map *map);

/**
 * Delete a map
 */
void Map_Delete(Map *map);

#endif /* INCLUDE_MAP_H */
