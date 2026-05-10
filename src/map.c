#include <map.h>

int MAP_WIDTH = 0;
int MAP_HEIGHT = 0;
int MAP_MAX_LENGTH = 0;
SDL_FPoint MAP_DEFAULT_POS = { 0.0f, 0.0f };

Map Map_Init()
{
	Map map;
	map.object.rect.x = map.object.rect.y = 0;
	map.object.direction = 0.0f;

	char line[1024];
	FILE *file = fopen(MAP_FILE, "r");
	if (!file) {
		perror("Fail to open map file");
		exit(EXIT_FAILURE);
	}

	fgets(line, sizeof(line), file);
	sscanf(line, "%d %d", &MAP_WIDTH, &MAP_HEIGHT);
	map.object.rect.w = MAP_WIDTH;
	map.object.rect.h = MAP_HEIGHT;
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

	map.surface = SDL_CreateSurface(MAP_WIDTH * WINDOW_SCALE,
					MAP_HEIGHT * WINDOW_SCALE,
					RENDER_PIXEL_FORMAT);
	map.object.texture = Camera_CreateTextureFromSurface(map.surface);

	// Textures
	SDL_Surface *fileSurface = SDL_LoadBMP(MAP_TEXTURE_FILE);
	// Floor texture
	SDL_Rect rect = { MAP_TEXTURE_FLOOR.x * MAP_TEXTURE_SIZE,
			  MAP_TEXTURE_FLOOR.y * MAP_TEXTURE_SIZE,
			  MAP_TEXTURE_SIZE, MAP_TEXTURE_SIZE };
	map.floor = SDL_CreateSurface(MAP_TEXTURE_SIZE, MAP_TEXTURE_SIZE,
				      RENDER_PIXEL_FORMAT);
	SDL_BlitSurface(fileSurface, &rect, map.floor, NULL);

	// Wall texture
	rect.x = MAP_TEXTURE_WALL.x * MAP_TEXTURE_SIZE;
	rect.y = MAP_TEXTURE_WALL.y * MAP_TEXTURE_WALL_HEIGHT;
	rect.h = MAP_TEXTURE_WALL_HEIGHT;
	map.wall = SDL_CreateSurface(MAP_TEXTURE_SIZE, MAP_TEXTURE_WALL_HEIGHT,
				     RENDER_PIXEL_FORMAT);
	SDL_BlitSurface(fileSurface, &rect, map.wall, NULL);

	SDL_DestroySurface(fileSurface);

	return map;
}

void Map_Update(Map *map)
{
	// Floor
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
			SDL_BlitSurfaceScaled(map->floor, NULL, map->surface,
					      &rect, SDL_SCALEMODE_NEAREST);
		}
	}

	// Wall
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
			rect.y = row * WINDOW_SCALE - MAP_WALL_DELTA;
			SDL_BlitSurfaceScaled(map->wall, NULL, map->surface,
					      &rect, SDL_SCALEMODE_NEAREST);
		}
	}
	SDL_UpdateTexture(map->object.texture, NULL, map->surface->pixels,
			  map->surface->pitch);
}

Render_Boundary Map_GetBoundary()
{
	Render_Boundary boundary;
	boundary.left = boundary.up = 0;
	boundary.right = MAP_WIDTH;
	boundary.down = MAP_HEIGHT;
	return boundary;
}

bool Map_IsHit(Map *map, float x, float y)
{
	if (x < 0 || y < 0 || x > MAP_WIDTH || y > MAP_HEIGHT) {
		return true;
	} else if (map->list[(int)y * MAP_WIDTH + (int)x] == MAP_CODE_WALL) {
		return true;
	}
	return false;
}

void Map_Delete(Map *map)
{
	SDL_DestroyTexture(map->object.texture);
	SDL_DestroySurface(map->surface);
	free(map->list);
}
