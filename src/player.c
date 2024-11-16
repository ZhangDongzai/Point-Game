#include <player.h>


Player* createPlayer(int x, int y, SDL_Color color) {
    Player *player = (Player *)malloc(sizeof(Player));

    player->x = player->fx = x;
    player->y = player->fy = y;
    player->direction = 0.0f;
    player->color = color;

    return player;
}


void updatePlayer(Player *player, int deltaTimeMs) {
    float x = 0.0f;
    float y = 0.0f;
    float speed = PLAYER_SPEED_MS * deltaTimeMs;
    if (app.keyBoardState[SDL_SCANCODE_W]) {
        x += speed * cos(player->direction);
        y += speed * sin(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_S]) {
        x -= speed * cos(player->direction);
        y -= speed * sin(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_A]) {
        x += speed * sin(player->direction);
        y -= speed * cos(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_D]) {
        x -= speed * sin(player->direction);
        y += speed * cos(player->direction);
    }
    if (app.keyBoardState[SDL_SCANCODE_J]) player->direction -= deltaTimeMs / 1000.0f;
    if (app.keyBoardState[SDL_SCANCODE_L]) player->direction += deltaTimeMs / 1000.0f;

    player->fx += x;
    player->fy += y;
    player->x = (int) player->fx;
    player->y = (int) player->fy;
}


void renderPlayer(SDL_Renderer *renderer, Player *player) {
    SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
    drawFillCircle(renderer, PLAYER_RADUIS, player->x, player->y);
    SDL_RenderDrawLine(renderer, player->x, player->y,
        player->x + 1000.0f * cos(player->direction),
        player->y + 1000.0f * sin(player->direction));
}


void destroyPlayer(Player *player) {
    free(player);
}
