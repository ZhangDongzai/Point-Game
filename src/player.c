#include <player.h>


Player* Player_Create() {
    Player* player = (Player *)calloc(1, sizeof(Player));
}

int* Player_GetPos(Player *player) {
    return player->pos;
}

float Player_GetDirection(Player *player) {
    return player->direction;
}

void Player_Delete(Player *player) {
    free(player);
}
