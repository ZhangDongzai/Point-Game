#include <map.h>

int MAP_WIDTH = 0;
int MAP_HEIGHT = 0;
int MAP_MAX_LENGTH = 0;
SDL_FPoint MAP_DEFAULT_POS = { 0.0f, 0.0f };

void Map_Init(Map *map, Enemys *enemys)
{
	char line[1024];
	FILE *file = fopen(MAP_FILE, "r");
	if (!file) {
		perror("Fail to open map file");
		exit(EXIT_FAILURE);
	}

	fgets(line, sizeof(line), file);
	sscanf(line, "%d %d", &MAP_WIDTH, &MAP_HEIGHT);
	map->boundary = (SDL_FRect){ 0, 0, MAP_WIDTH, MAP_HEIGHT };
	MAP_MAX_LENGTH = MAP_WIDTH + MAP_HEIGHT;
	map->list = (int *)calloc(MAP_WIDTH * MAP_HEIGHT, sizeof(int));

	fgets(line, sizeof(line), file);
	sscanf(line, "%f %f", &MAP_DEFAULT_POS.x, &MAP_DEFAULT_POS.y);

	fgets(line, sizeof(line), file);
	SDL_FPoint pos;
	for (char *i = line, *temp; *i != '\0'; i++) {
		pos.x = strtof(i, &temp);
		i = temp + 1;
		pos.y = strtof(i, &temp);
		i = temp;
		Enemy_Create(enemys, &pos);
	}

	for (int row = 0; row < MAP_HEIGHT; row++) {
		fgets(line, sizeof(line), file);
		for (int column = 0; column < MAP_WIDTH; column++) {
			map->list[row * MAP_WIDTH + column] = line[column];
		}
	}

	fclose(file);

	// Textures
	SDL_Surface *fileSurface = SDL_LoadPNG(MAP_TEXTURE_FILE);
	SDL_Rect rect = { MAP_TEXTURE_FLOOR.x * MAP_TEXTURE_SIZE,
			  MAP_TEXTURE_FLOOR.y * MAP_TEXTURE_SIZE,
			  MAP_TEXTURE_SIZE, MAP_TEXTURE_SIZE };
	SDL_Surface *floor = SDL_CreateSurface(WINDOW_SCALE, WINDOW_SCALE,
					       RENDER_PIXEL_FORMAT);
	SDL_BlitSurfaceScaled(fileSurface, &rect, floor, NULL,
			      SDL_SCALEMODE_NEAREST);
	map->floor = Camera_CreateTextureFromSurface(floor);
	SDL_DestroySurface(floor);

	rect.x = MAP_TEXTURE_WALL.x * MAP_TEXTURE_SIZE;
	rect.y = MAP_TEXTURE_WALL.y * MAP_TEXTURE_WALL_HEIGHT;
	rect.h = MAP_TEXTURE_WALL_HEIGHT;
	SDL_Surface *wall = SDL_CreateSurface(WINDOW_SCALE,
					      WINDOW_SCALE + MAP_WALL_DELTA,
					      RENDER_PIXEL_FORMAT);
	SDL_BlitSurfaceScaled(fileSurface, &rect, wall, NULL,
			      SDL_SCALEMODE_NEAREST);
	map->wall = Camera_CreateTextureFromSurface(wall);
	SDL_DestroySurface(wall);
	SDL_DestroySurface(fileSurface);
}

void Map_Render(SDL_Renderer *renderer, Map *map, SDL_FPoint *point)
{
	SDL_FPoint screenPos = Camera_GetPosOnScreen(point);
	SDL_FRect rect = { screenPos.x, screenPos.y, WINDOW_SCALE,
			   WINDOW_SCALE };
	SDL_Texture *texture = NULL;
	for (int column = 0; column < (int)WINDOW_WIDTH_SCALE + 1; column++) {
		rect.x = screenPos.x + column * WINDOW_SCALE;
		rect.y = screenPos.y;
		switch (map->list[(int)point->y * MAP_WIDTH + (int)point->x +
				  column]) {
		case MAP_CODE_NULL:
			continue;
		case MAP_CODE_FLOOR:
			rect.h = WINDOW_SCALE;
			texture = map->floor;
			break;
		case MAP_CODE_WALL:
			rect.y -= MAP_WALL_DELTA;
			rect.h = WINDOW_SCALE + MAP_WALL_DELTA;
			texture = map->wall;
			break;
		}
		SDL_RenderTexture(renderer, texture, NULL, &rect);
	}
}

bool Map_IsPointHit(Map *map, float x, float y)
{
	if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) {
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
	       Map_IsPointHit(map, rect->x + rect->w, rect->y + rect->h);
}

void Map_Delete(Map *map)
{
	SDL_DestroyTexture(map->floor);
	SDL_DestroyTexture(map->wall);
	free(map->list);
}
