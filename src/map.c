#include <map.h>

int mapList[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

Map* Map_Create() {
    Map *map = (Map *)calloc(1, sizeof(Map));
    map->rect.x = map->rect.y = 0;
    map->rect.w = MAP_WIDTH;
    map->rect.h = MAP_HEIGHT;

    SDL_Surface *surface = SDL_CreateSurface(MAP_WIDTH * WINDOW_SCALE, MAP_HEIGHT * WINDOW_SCALE, SDL_PIXELFORMAT_RGBA32);
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);
    SDL_FRect rect = {0, 0, WINDOW_SCALE, WINDOW_SCALE};

    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int column = 0; column < MAP_WIDTH; column++) {
            switch (mapList[row][column])
            {
            case MAP_CODE_WALL:
                SDL_SetRenderDrawColor(renderer, MAP_COLOR_WALL.r, MAP_COLOR_WALL.g, MAP_COLOR_WALL.b, MAP_COLOR_WALL.a);
                break;
            case MAP_CODE_FLOOR:
                SDL_SetRenderDrawColor(renderer, MAP_COLOR_FLOOR.r, MAP_COLOR_FLOOR.g, MAP_COLOR_FLOOR.b, MAP_COLOR_FLOOR.a);
                break;
            }
            rect.x = column * WINDOW_SCALE;
            rect.y = row * WINDOW_SCALE;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);

    map->texture = Camera_CreateTextureFromSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroySurface(surface);

    return map;
}

Render_Boundary* Map_GetBoundary() {
    Render_Boundary *boundary = (Render_Boundary *)malloc(sizeof(Render_Boundary));
    boundary->left = boundary->up = 0;
    boundary->right = MAP_WIDTH;
    boundary->down = MAP_HEIGHT;
    return boundary;
}

bool Map_IsHit(float x, float y) {
    if (x < 0 || y < 0 || x > MAP_WIDTH || y > MAP_HEIGHT) {
        return true;
    } else if (mapList[(int)y][(int)x] == 1) {
        return true;
    }
    return false;
}

void Map_Delete(Map *map) {
    SDL_DestroyTexture(map->texture);
    free(map);
}
