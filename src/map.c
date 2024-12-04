#include <map.h>


Map loadMap() {
    Map map = (int**) malloc(MAP_ROW * sizeof(int*));
    for (int i = 0; i < MAP_ROW; i++) {
        map[i] = (int*) malloc(MAP_COLUMN * sizeof(int));
    }
    FILE *mapFile = fopen(MAP_PATH, "r");
    char line[MAP_COLUMN + 2];
    for (int row = 0; row < MAP_ROW; row++) {
        fgets(line, MAP_COLUMN + 2, mapFile);
        for (int column = 0; column < MAP_COLUMN; column++) {
            if (line[column] == '\0' || line[column] == '\n') break;
            map[row][column] = line[column] - '0';
        }
    }
    fclose(mapFile);
    return map;
}


void renderMap(SDL_Renderer *renderer, Map map) {
    for (int row = 0; row < MAP_ROW; row++) {
        for (int column = 0; column < MAP_COLUMN; column++) {
            SDL_Rect rect = {column * MAP_WIDTH, row * MAP_HEIGHT,
                MAP_WIDTH, MAP_HEIGHT};
            if (map[row][column] == MAP_AIR) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else if (map[row][column] == MAP_WALL) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}


bool isHitMap(Map map, int x, int y) {
    if (x <= 0 || y <= 0 || x >= MAP_WIDTH * MAP_COLUMN || y >= MAP_HEIGHT * MAP_ROW)
        return false;
    if (map[y / MAP_HEIGHT][x / MAP_WIDTH] == MAP_WALL)
        return true;
    return false;
}
