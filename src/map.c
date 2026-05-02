#include <map.h>
#include <stdio.h>

int MAP_WIDTH = 0;
int MAP_HEIGHT = 0;
int MAP_MAX_LENGTH = 0;

Map *Map_Init()
{
	Map *map = (Map *)calloc(1, sizeof(Map));
	map->object.rect.x = map->object.rect.y = 0;

	char line[1024];
	FILE *file = fopen(MAP_FILE, "r");
	if (!file) {
		perror("Fail to open map file");
		exit(EXIT_FAILURE);
	}

	fgets(line, sizeof(line), file);
	sscanf(line, "%d %d", &MAP_WIDTH, &MAP_HEIGHT);
	map->object.rect.w = MAP_WIDTH;
	map->object.rect.h = MAP_HEIGHT;
	MAP_MAX_LENGTH = MAP_WIDTH + MAP_HEIGHT;
	map->list = (int *)calloc(MAP_WIDTH * MAP_HEIGHT, sizeof(int));
	
	for (int row = 0; row < MAP_HEIGHT; row++) {
		fgets(line, sizeof(line), file);
		for (int column = 0; column < MAP_WIDTH; column++) {
			map->list[row * MAP_WIDTH + column] = line[column] - '0';
		}
	}

	fclose(file);
	return map;
}

void Map_Clean(Map *map)
{
	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int column = 0; column < MAP_WIDTH; column++) {
			if (map->list[row * MAP_WIDTH + column] == MAP_CODE_WALL_LIGHT)
				map->list[row * MAP_WIDTH + column] = MAP_CODE_WALL;
		}
	}
}

void Map_Update(Map *map)
{
	SDL_Surface *surface = SDL_CreateSurface(MAP_WIDTH * WINDOW_SCALE,
						 MAP_HEIGHT * WINDOW_SCALE,
						 SDL_PIXELFORMAT_RGBA32);
	SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);
	SDL_FRect rect = { 0, 0, WINDOW_SCALE, WINDOW_SCALE };

	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int column = 0; column < MAP_WIDTH; column++) {
			switch (map->list[row * MAP_WIDTH + column]) {
			case MAP_CODE_WALL_LIGHT:
				SDL_SetRenderDrawColor(renderer,
						       MAP_COLOR_WALL_LIGHT.r,
						       MAP_COLOR_WALL_LIGHT.g,
						       MAP_COLOR_WALL_LIGHT.b,
						       MAP_COLOR_WALL_LIGHT.a);
				break;
			case MAP_CODE_WALL:
				SDL_SetRenderDrawColor(renderer,
						       MAP_COLOR_WALL.r,
						       MAP_COLOR_WALL.g,
						       MAP_COLOR_WALL.b,
						       MAP_COLOR_WALL.a);
				break;
			case MAP_CODE_FLOOR:
				SDL_SetRenderDrawColor(renderer,
						       MAP_COLOR_FLOOR.r,
						       MAP_COLOR_FLOOR.g,
						       MAP_COLOR_FLOOR.b,
						       MAP_COLOR_FLOOR.a);
				break;
			}
			rect.x = column * WINDOW_SCALE;
			rect.y = row * WINDOW_SCALE;
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(map->object.texture);
	map->object.texture = Camera_CreateTextureFromSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroySurface(surface);
}

Render_Boundary *Map_GetBoundary()
{
	Render_Boundary *boundary =
		(Render_Boundary *)malloc(sizeof(Render_Boundary));
	boundary->left = boundary->up = 0;
	boundary->right = MAP_WIDTH;
	boundary->down = MAP_HEIGHT;
	return boundary;
}

bool Map_IsHit(Map *map, float x, float y)
{
	if (x < 0 || y < 0 || x > MAP_WIDTH || y > MAP_HEIGHT) {
		return true;
	} else if (map->list[(int)y * MAP_WIDTH + (int)x] == MAP_CODE_WALL ||
		   map->list[(int)y * MAP_WIDTH + (int)x] == MAP_CODE_WALL_LIGHT) {
		return true;
	}
	return false;
}

void Map_SetLightWall(Map *map, float x, float y)
{
	if (map->list[(int)y * MAP_WIDTH + (int)x] == MAP_CODE_WALL)
		map->list[(int)y * MAP_WIDTH + (int)x] = MAP_CODE_WALL_LIGHT;
}

void Map_Delete(Map *map)
{
	SDL_DestroyTexture(map->object.texture);
	free(map->list);
	free(map);
}
