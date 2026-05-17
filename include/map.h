#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

#include <camera.h>
#include <common.h>

extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern int MAP_MAX_LENGTH;
extern SDL_FPoint MAP_DEFAULT_POS;

typedef enum {
	MAP_CODE_FLOOR = '0',
	MAP_CODE_WALL = '1',
	MAP_CODE_NULL = 'N',
} MAP_CODE;

typedef struct {
	// Texture
	SDL_Surface *floorTexture;
	SDL_Surface *wallTexture;

	int *list;
	SDL_Surface *surface;
	Render_Object floor;
	Render_Object wall;
} Map;

/**
 * Init map from file
 *
 * \returns the map context
 */
Map Map_Init();

/**
 * Tell the object if it hits walls
 *
 * \returns a bool value
 */
bool Map_IsPointHit(Map *map, float x, float y);
bool Map_IsRectHit(Map *map, SDL_FRect *rect);

/**
 * Render the map
 */
void Map_Render(Map *map);

/**
 * Delete a map
 */
void Map_Delete(Map *map);

#endif /* INCLUDE_MAP_H */
