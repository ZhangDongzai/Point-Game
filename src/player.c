#include <player.h>


Player* Player_Create() {
    Player* player = (Player *)calloc(1, sizeof(Player));
    player->rect.x = PLAYER_DEFAULT_POS[0];
    player->rect.y = PLAYER_DEFAULT_POS[1];
    player->rect.w = player->rect.h = PLAYER_SIZE;
    player->direction = PLAYER_DEFAULT_DIRECTION;
    player->color = PLAYER_COLOR;
    player->shape = PLAYER_SHAPE;
    return player;
}

void Player_Update(Player *player, Uint64 deltaTime, BulletList *bulletList) {
    const bool *keyboardState = SDL_GetKeyboardState(NULL);
    float sin = PLAYER_MOVE_SPEED * deltaTime / 1000.0f * SDL_sinf(player->direction);
    float cos = PLAYER_MOVE_SPEED * deltaTime / 1000.0f * SDL_cosf(player->direction);
    float turn = PLAYER_TURN_SPEED * deltaTime / 1000.0f;
    float x = 0, y = 0;
    if (keyboardState[SDL_SCANCODE_W]) {
        x = cos;
        y = sin;
    } if (keyboardState[SDL_SCANCODE_S]) {
        x = -cos;
        y = -sin;
    }

    if (Map_IsHit(player->rect.x + x, player->rect.y) == false) {
        player->rect.x += x;
    } if (Map_IsHit(player->rect.x, player->rect.y + y) == false) {
        player->rect.y += y;
    }
    
    if (keyboardState[SDL_SCANCODE_A]) {
        player->direction -= turn;
    } if (keyboardState[SDL_SCANCODE_D]) {
        player->direction += turn;
    }

    if (keyboardState[SDL_SCANCODE_J]) {
        Bullet_Create(player, bulletList);
    }
}

void Player_Delete(Player *player) {
    free(player);
}
