#include <map.h>


Map loadMap() {
    Map map;
    map = (int**) malloc(MAP_HEIGHT * sizeof(int*));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        map[i] = (int*) malloc(MAP_WIDTH * sizeof(int));
    }
    FILE *mapFile = fopen(MAP_PATH, "r");
    char line[MAP_WIDTH + 2];
    for (int row = 0; row < MAP_HEIGHT; row++) {
        fgets(line, MAP_WIDTH + 2, mapFile);
        for (int column = 0; column < MAP_WIDTH; column++) {
            if (line[column] == '\0' || line[column] == '\n') break;
            map[row][column] = line[column] - '0';
        }
    }
    return map;
}


void renderMap(SDL_Renderer *renderer, Map map) {
    const int squareWidth = WINDOW_WIDTH / MAP_WIDTH;
    const int squareHeight = WINDOW_HEIGHT / MAP_HEIGHT;
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int column = 0; column < MAP_WIDTH; column++) {
            SDL_Rect rect = {column * squareWidth, row * squareHeight,
                squareWidth, squareHeight};
            if (map[row][column] == MAP_COLOR_BLACK) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else if (map[row][column] == MAP_COLOR_WHITE) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
