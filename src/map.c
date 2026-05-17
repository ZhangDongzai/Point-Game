#include <map.h>

int MAP_WIDTH = 0;
int MAP_HEIGHT = 0;
int MAP_MAX_LENGTH = 0;
SDL_FPoint MAP_DEFAULT_POS = { 0.0f, 0.0f };

Map Map_Init()
{
	Map map;
	map.floor.srcrect.x = map.floor.srcrect.y = 0;
	map.wall.srcrect.x = map.wall.srcrect.y = 0;
	map.floor.dstrect.x = map.floor.dstrect.y = map.wall.dstrect.x = 0;
	map.wall.dstrect.y = -MAP_WALL_DELTA_SCALE;
	map.floor.direction = map.wall.direction = 0.0f;
	map.floor.flipMode = map.wall.flipMode = SDL_FLIP_NONE;

	char line[1024];
	FILE *file = fopen(MAP_FILE, "r");
	if (!file) {
		perror("Fail to open map file");
		exit(EXIT_FAILURE);
	}

	fgets(line, sizeof(line), file);
	sscanf(line, "%d %d", &MAP_WIDTH, &MAP_HEIGHT);
	map.floor.dstrect.w = map.wall.dstrect.w = MAP_WIDTH;
	map.floor.dstrect.h = map.wall.dstrect.h = MAP_HEIGHT;
	map.floor.srcrect.w = map.wall.srcrect.w = MAP_WIDTH * WINDOW_SCALE;
	map.floor.srcrect.h = map.wall.srcrect.h = MAP_HEIGHT * WINDOW_SCALE;
	MAP_MAX_LENGTH = MAP_WIDTH + MAP_HEIGHT;
	map.list = (int *)calloc(MAP_WIDTH * MAP_HEIGHT, sizeof(int));

	fgets(line, sizeof(line), file);
	sscanf(line, "%f %f", &MAP_DEFAULT_POS.x, &MAP_DEFAULT_POS.y);

	for (int row = 0; row < MAP_HEIGHT; row++) {
		fgets(line, sizeof(line), file);
		for (int column = 0; column < MAP_WIDTH; column++) {
			map.list[row * MAP_WIDTH + column] = line[column];
		}
	}

	fclose(file);

	map.surface = SDL_CreateSurface(
		map.floor.srcrect.w, map.floor.srcrect.h, RENDER_PIXEL_FORMAT);
	map.floor.texture = Camera_CreateTextureFromSurface(map.surface);
	map.wall.texture = Camera_CreateTextureFromSurface(map.surface);

	// Textures
	SDL_Surface *fileSurface = IMG_Load(MAP_TEXTURE_FILE);
	// Floor texture
	SDL_Rect rect = { MAP_TEXTURE_FLOOR.x * MAP_TEXTURE_SIZE,
			  MAP_TEXTURE_FLOOR.y * MAP_TEXTURE_SIZE,
			  MAP_TEXTURE_SIZE, MAP_TEXTURE_SIZE };
	map.floorTexture = SDL_CreateSurface(MAP_TEXTURE_SIZE, MAP_TEXTURE_SIZE,
					     RENDER_PIXEL_FORMAT);
	SDL_BlitSurface(fileSurface, &rect, map.floorTexture, NULL);

	// Wall texture
	rect.x = MAP_TEXTURE_WALL.x * MAP_TEXTURE_SIZE;
	rect.y = MAP_TEXTURE_WALL.y * MAP_TEXTURE_WALL_HEIGHT;
	rect.h = MAP_TEXTURE_WALL_HEIGHT;
	map.wallTexture = SDL_CreateSurface(
		MAP_TEXTURE_SIZE, MAP_TEXTURE_WALL_HEIGHT, RENDER_PIXEL_FORMAT);
	SDL_BlitSurface(fileSurface, &rect, map.wallTexture, NULL);

	SDL_DestroySurface(fileSurface);

	return map;
}

void Map_Update(Map *map)
{
	// Floor
	SDL_ClearSurface(map->surface, 0.0f, 0.0f, 0.0f, 0.0f);
	SDL_Rect rect = { 0, 0, WINDOW_SCALE, WINDOW_SCALE };
	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int column = 0; column < MAP_WIDTH; column++) {
			switch (map->list[row * MAP_WIDTH + column]) {
			case MAP_CODE_NULL:
			case MAP_CODE_WALL:
				continue;
			case MAP_CODE_FLOOR:
				break;
			}
			rect.x = column * WINDOW_SCALE;
			rect.y = row * WINDOW_SCALE;
			SDL_BlitSurfaceScaled(map->floorTexture, NULL,
					      map->surface, &rect,
					      SDL_SCALEMODE_NEAREST);
		}
	}
	SDL_UpdateTexture(map->floor.texture, NULL, map->surface->pixels,
			  map->surface->pitch);

	// Wall
	SDL_ClearSurface(map->surface, 0.0f, 0.0f, 0.0f, 0.0f);
	rect.h = (float)MAP_TEXTURE_WALL_HEIGHT / (float)MAP_TEXTURE_SIZE *
		 WINDOW_SCALE;
	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int column = 0; column < MAP_WIDTH; column++) {
			switch (map->list[row * MAP_WIDTH + column]) {
			case MAP_CODE_NULL:
			case MAP_CODE_FLOOR:
				continue;
			case MAP_CODE_WALL:
				break;
			}
			rect.x = column * WINDOW_SCALE;
			rect.y = row * WINDOW_SCALE;
			SDL_BlitSurfaceScaled(map->wallTexture, NULL,
					      map->surface, &rect,
					      SDL_SCALEMODE_NEAREST);
		}
	}
	SDL_UpdateTexture(map->wall.texture, NULL, map->surface->pixels,
			  map->surface->pitch);
}

bool Map_IsPointHit(Map *map, float x, float y)
{
	if (x < 0 || y < 0 || x > MAP_WIDTH || y > MAP_HEIGHT) {
		return true;
	} else if (map->list[(int)y * MAP_WIDTH + (int)x] == MAP_CODE_WALL) {
		return true;
	}
	return false;
}

bool Map_IsRectHit(Map *map, SDL_FRect *rect)
{
	return Map_IsPointHit(map, rect->x, rect->y) ||
	       Map_IsPointHit(map, rect->x + rect->w, rect->y) ||
	       Map_IsPointHit(map, rect->x, rect->y + rect->h) ||
	       Map_IsPointHit(map, rect->x + rect->w, rect->y + rect->w);
}

void Map_Delete(Map *map)
{
	SDL_DestroyTexture(map->floor.texture);
	SDL_DestroyTexture(map->floor.texture);
	SDL_DestroySurface(map->surface);
	free(map->list);
}
