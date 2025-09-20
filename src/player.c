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
    Render_Object *object = (Render_Object *)malloc(sizeof(Render_Object));
    memcpy(object->pos, player->pos, sizeof(player->pos));
    object->size = PLAYER_SIZE;
    object->color = PLAYER_COLOR;
    object->shape = RENDER_SHAPE_CIRCLE;

    return object;
}

void Player_Delete(Player *player) {
    free(player);
}
