#include <map.h>

int MAP_WIDTH = 0;
int MAP_HEIGHT = 0;
int MAP_MAX_LENGTH = 0;

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

	for (int row = 0; row < MAP_HEIGHT; row++) {
		fgets(line, sizeof(line), file);
		for (int column = 0; column < MAP_WIDTH; column++) {
			map.list[row * MAP_WIDTH + column] = line[column] - '0';
		}
	}

	fclose(file);
	
	map.surface = SDL_CreateSurface(MAP_WIDTH * WINDOW_SCALE,
					MAP_HEIGHT * WINDOW_SCALE,
					SDL_PIXELFORMAT_RGBA32);
	map.renderer = SDL_CreateSoftwareRenderer(map.surface);
	map.object.texture = Camera_CreateTextureFromSurface(map.surface);
	
	return map;
}

void Map_Update(Map *map)
{
	SDL_FRect rect = { 0, 0, WINDOW_SCALE, WINDOW_SCALE };

	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int column = 0; column < MAP_WIDTH; column++) {
			switch (map->list[row * MAP_WIDTH + column]) {
			case MAP_CODE_FLOOR:
				SDL_SetRenderDrawColor(map->renderer,
						       MAP_COLOR_FLOOR.r,
						       MAP_COLOR_FLOOR.g,
						       MAP_COLOR_FLOOR.b,
						       MAP_COLOR_FLOOR.a);
				break;
			case MAP_CODE_WALL:
				SDL_SetRenderDrawColor(map->renderer,
						       MAP_COLOR_WALL.r,
						       MAP_COLOR_WALL.g,
						       MAP_COLOR_WALL.b,
						       MAP_COLOR_WALL.a);
				break;
			case MAP_CODE_WATER:
				SDL_SetRenderDrawColor(map->renderer,
						       MAP_COLOR_WATER.r,
						       MAP_COLOR_WATER.g,
						       MAP_COLOR_WATER.b,
						       MAP_COLOR_WATER.a);
				break;
			case MAP_CODE_GRASS:
				SDL_SetRenderDrawColor(map->renderer,
						       MAP_COLOR_GRASS.r,
						       MAP_COLOR_GRASS.g,
						       MAP_COLOR_GRASS.b,
						       MAP_COLOR_GRASS.a);
				break;
			}
			rect.x = column * WINDOW_SCALE;
			rect.y = row * WINDOW_SCALE;
			SDL_RenderFillRect(map->renderer, &rect);
		}
	}
	SDL_RenderPresent(map->renderer);
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
	SDL_DestroyRenderer(map->renderer);
	SDL_DestroySurface(map->surface);
	free(map->list);
}
