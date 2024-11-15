#include <player.h>


Player* createPlayer(int x, int y, SDL_Color color) {
    Player *player = (Player *)malloc(sizeof(Player));

    player->x = player->fx = x;
    player->y = player->fy = y;
    player->color = color;

    return player;
}


void updatePlayer(Player *player, int deltaTimeMs) {
    if (app.keyBoardState[SDL_SCANCODE_W]) {
        player->fy -= PLAYER_SPEED_MS * deltaTimeMs;
    }
    if (app.keyBoardState[SDL_SCANCODE_S]) {
        player->fy += PLAYER_SPEED_MS * deltaTimeMs;
    }
    if (app.keyBoardState[SDL_SCANCODE_A]) {
        player->fx -= PLAYER_SPEED_MS * deltaTimeMs;
    }
    if (app.keyBoardState[SDL_SCANCODE_D]) {
        player->fx += PLAYER_SPEED_MS * deltaTimeMs;
    }
    player->x = (int) player->fx;
    player->y = (int) player->fy;
}


void renderPlayer(SDL_Renderer *renderer, Player *player) {
    SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
    drawFillCircle(renderer, PLAYER_RADUIS, player->x, player->y);
}


void destroyPlayer(Player *player) {
    free(player);
}
