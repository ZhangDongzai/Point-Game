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
    float speed = PLAYER_SPEED_MS * deltaTimeMs;
    if (app.keyBoardState[SDL_SCANCODE_W]) {
        x += speed * cosf(player->direction);
        y += speed * sinf(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_S]) {
        x -= speed * cosf(player->direction);
        y -= speed * sinf(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_A]) {
        x += speed * sinf(player->direction);
        y -= speed * cosf(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_D]) {
        x -= speed * sinf(player->direction);
        y += speed * cosf(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_J]) {
        player->direction -= (float) deltaTimeMs / 1000.0f;
    }
    if (app.keyBoardState[SDL_SCANCODE_L]) {
        player->direction += (float) deltaTimeMs / 1000.0f;
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
<<<<<<< HEAD
    drawFillCircle(renderer, PLAYER_RADIUS, player->x, player->y);
    // SDL_RenderDrawLine(renderer, player->x, player->y,
    //     player->x + (int) (cosf(player->direction) * 1000.0f),
    //     player->y + (int) (sinf(player->direction) * 1000.0f));
=======
    drawFillCircle(renderer, PLAYER_RADUIS, player->x, player->y);
    SDL_RenderDrawLine(renderer, player->x, player->y,
        player->x + (int) floorf(1000.0f * cosf(player->direction)),
        player->y + (int) floorf(1000.0f * sinf(player->direction)));
>>>>>>> parent of 6b7b371 (fix: var name)
}


void destroyPlayer(Player *player) {
    free(player);
}
