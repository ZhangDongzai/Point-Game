#include <player.h>

PlayerBasic playerBasic = {WHITE, 50, (SDL_Point) {640, 360}};


Player* create_player() {
    // Create player
    Player* player = (Player *)malloc(sizeof(Player));
    player->rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    player->playerBasic = &playerBasic;
    int size = playerBasic.radius * 2;
    player->rect->w = player->rect->h = size;
    player->rect->x = playerBasic.center.x - playerBasic.radius;
    player->rect->y = playerBasic.center.y - playerBasic.radius;

    // Draw
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, size, size,
        32, SDL_PIXELFORMAT_RGBA8888);
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);
    SDL_Point center = {playerBasic.radius, playerBasic.radius};
    draw_circle(renderer, center, playerBasic.radius, playerBasic.color);
    SDL_RenderPresent(renderer);
    player->texture = SDL_CreateTextureFromSurface(app.renderer, surface);

    // Destroy
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);

    return player;
}


void destroy_player(Player *player) {
    SDL_DestroyTexture(player->texture);
    free(player);
}
