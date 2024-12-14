#include <map.h>


Map loadMap() {
<<<<<<< HEAD
    Map map = (int**) malloc(MAP_ROW * sizeof(int*));
    for (int i = 0; i < MAP_ROW; i++) {
        map[i] = (int*) malloc(MAP_COLUMN * sizeof(int));
=======
    Map map;
    map = (int**) malloc(MAP_HEIGHT * sizeof(int*));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        map[i] = (int*) malloc(MAP_WIDTH * sizeof(int));
>>>>>>> parent of 6b7b371 (fix: var name)
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
<<<<<<< HEAD
    for (int row = 0; row < MAP_ROW; row++) {
        for (int column = 0; column < MAP_COLUMN; column++) {
            SDL_Rect rect = {column * MAP_WIDTH, row * MAP_HEIGHT,
                MAP_WIDTH, MAP_HEIGHT};
            if (map[row][column] == MAP_AIR) {
=======
    const int squareWidth = WINDOW_WIDTH / MAP_WIDTH;
    const int squareHeight = WINDOW_HEIGHT / MAP_HEIGHT;
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int column = 0; column < MAP_WIDTH; column++) {
            SDL_Rect rect = {column * squareWidth, row * squareHeight,
                squareWidth, squareHeight};
            if (map[row][column] == MAP_COLOR_BLACK) {
>>>>>>> parent of 6b7b371 (fix: var name)
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else if (map[row][column] == MAP_COLOR_WHITE) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
<<<<<<< HEAD


bool isHitMap(Map map, int x, int y) {
    if (x <= 0 || y <= 0 || x >= MAP_WIDTH * MAP_COLUMN || y >= MAP_HEIGHT * MAP_ROW)
        return false;
    if (map[y / MAP_HEIGHT][x / MAP_WIDTH] == MAP_WALL)
        return true;
    return false;
}
=======
>>>>>>> parent of 6b7b371 (fix: var name)
