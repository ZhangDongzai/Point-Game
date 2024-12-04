#include <player.h>


Player* createPlayer(int x, int y, SDL_Color color) {
    Player *player = (Player *)malloc(sizeof(Player));

    player->x = x;
    player->fx = (float) x;
    player->y = y;
    player->fy = (float) y;
    player->direction = 0.0f;
    player->color = color;

    return player;
}


void updatePlayer(Player *player, unsigned int deltaTimeMs, Map map) {
    float x = 0.0f;
    float y = 0.0f;
    float moveSpeed = PLAYER_MOVE_SPEED_MS * (float) deltaTimeMs;
    float turnSpeed = PLAYER_TURN_SPEED_MS * (float) deltaTimeMs;
    if (app.keyBoardState[SDL_SCANCODE_W]) {
        x += moveSpeed * cosf(player->direction);
        y += moveSpeed * sinf(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_S]) {
        x -= moveSpeed * cosf(player->direction);
        y -= moveSpeed * sinf(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_A]) {
        x += moveSpeed * sinf(player->direction);
        y -= moveSpeed * cosf(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_D]) {
        x -= moveSpeed * sinf(player->direction);
        y += moveSpeed * cosf(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_J]) {
        player->direction -= turnSpeed;
    }
    if (app.keyBoardState[SDL_SCANCODE_L]) {
        player->direction += turnSpeed;
    }

    if (!isHitMap(map, (int) (player->fx + x), player->y)) {
        player->fx += x;
        player->x = (int) player->fx;
    }
    if (!isHitMap(map, player->x, (int) (player->fy + y))) {
        player->fy += y;
        player->y = (int) player->fy;
    }
}


void renderPlayer(SDL_Renderer *renderer, Player *player) {
    SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
    drawFillCircle(renderer, PLAYER_RADIUS, player->x, player->y);
    // SDL_RenderDrawLine(renderer, player->x, player->y,
    //     player->x + (int) (cosf(player->direction) * 1000.0f),
    //     player->y + (int) (sinf(player->direction) * 1000.0f));
}


void destroyPlayer(Player *player) {
    free(player);
}
