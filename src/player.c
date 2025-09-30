#include <player.h>


Player* Player_Create() {
    Player* player = (Player *)calloc(1, sizeof(Player));
    player->direction = PLAYER_DEFAULT_DIRECTION;
    memcpy(player->pos, PLAYER_DEFAULT_POS, sizeof(PLAYER_DEFAULT_POS));
    return player;
}

float* Player_GetPos(Player *player) {
    return player->pos;
}

float Player_GetDirection(Player *player) {
    return player->direction;
}

Render_Object* Player_GetRenderObject(Player *player) {
    static Render_Object *object = NULL;
    if (object == NULL) {
        object = (Render_Object *)malloc(sizeof(Render_Object));
    }
    
    memcpy(object->pos, player->pos, sizeof(player->pos));
    object->size = PLAYER_SIZE;
    object->color = PLAYER_COLOR;
    object->shape = PLAYER_SHAPE;
    object->direction = player->direction;

    return object;
}

void Player_Update(Player *player, Uint64 deltaTime) {
    const bool *keyboardState = SDL_GetKeyboardState(NULL);
    float sin = PLAYER_MOVE_SPEED * deltaTime / 1000.0f * SDL_sinf(player->direction);
    float cos = PLAYER_MOVE_SPEED * deltaTime / 1000.0f * SDL_cosf(player->direction);
    float turn = PLAYER_TURN_SPEED * deltaTime / 1000.0f;
    float x, y;
    if (keyboardState[SDL_SCANCODE_W]) {
        x = cos;
        y = sin;
    } if (keyboardState[SDL_SCANCODE_S]) {
        x = -cos;
        y = -sin;
    }

    if (Map_IsHit(player->pos[0] + x, player->pos[1]) == false) {
        player->pos[0] += x;
    } if (Map_IsHit(player->pos[0], player->pos[1] + y) == false) {
        player->pos[1] += y;
    }
    
    if (keyboardState[SDL_SCANCODE_A]) {
        player->direction -= turn;
    } if (keyboardState[SDL_SCANCODE_D]) {
        player->direction += turn;
    }
}

void Player_Delete(Player *player) {
    free(player);
}
