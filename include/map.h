#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

#include <enemy.h>
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
	SDL_Texture *floor;
	SDL_Texture *wall;

	SDL_FRect boundary;

	int *list;
} Map;

/**
 * Init map from file
 *
 * \returns the map context
 */
Map Map_Init(Enemys *enemys);

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
void Map_Render(SDL_Renderer *renderer, Map *map, SDL_FPoint *point);

/**
 * Delete a map
 */
void Map_Delete(Map *map);

#endif /* INCLUDE_MAP_H */
