#include <player.h>

PlayerBasic playerBasic = {WHITE, 50,
    (SDL_Point) {640, 360}, 100};


Player* CreatePlayer() {
    // Create
    Player* player = (Player *)malloc(sizeof(Player));
    player->f_rect = (SDL_FRect *)malloc(sizeof(SDL_FRect));
    player->rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    player->playerBasic = &playerBasic;
    int size = playerBasic.radius * 2;
    player->rect->w = player->rect->h = size;
    player->f_rect->w = player->f_rect->h = size;
    player->f_rect->x = playerBasic.center.x - playerBasic.radius;
    player->f_rect->y = playerBasic.center.y - playerBasic.radius;

    // Draw
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, size, size,
        32, SDL_PIXELFORMAT_RGBA8888);
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);
    SDL_Point center = {playerBasic.radius, playerBasic.radius};
    DrawCircle(renderer, center, playerBasic.radius, playerBasic.color);
    SDL_RenderPresent(renderer);
    player->texture = SDL_CreateTextureFromSurface(app.renderer, surface);

    // Destroy
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);

    return player;
}


void DestroyPlayer(Player *player) {
    SDL_DestroyTexture(player->texture);
    SDL_free(player->rect);
    SDL_free(player->f_rect);
    free(player);
}


void UpdatePlayer(Player *player) {
    if (app.keyboard_state[SDL_SCANCODE_W]) {
        player->f_rect->y = player->f_rect->y - player->playerBasic->speed_s
                          * app.delta_time_s;
    } if (app.keyboard_state[SDL_SCANCODE_S]) {
        player->f_rect->y = player->f_rect->y + player->playerBasic->speed_s
                          * app.delta_time_s;
    } if (app.keyboard_state[SDL_SCANCODE_A]) {
        player->f_rect->x = player->f_rect->x - player->playerBasic->speed_s
                          * app.delta_time_s;
    } if (app.keyboard_state[SDL_SCANCODE_D]) {
        player->f_rect->x = player->f_rect->x + player->playerBasic->speed_s
                          * app.delta_time_s;
    }

    player->rect->x = (int) player->f_rect->x;
    player->rect->y = (int) player->f_rect->y;
}
