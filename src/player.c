#include <player.h>


Player* Player_Create() {
    Player* player = (Player *)calloc(1, sizeof(Player));
    player->rect.x = PLAYER_DEFAULT_POS[0];
    player->rect.y = PLAYER_DEFAULT_POS[1];
    player->rect.w = player->rect.h = PLAYER_SIZE;
    player->direction = PLAYER_DEFAULT_DIRECTION;
    
    SDL_Surface *surface = SDL_CreateSurface(PLAYER_SIZE * WINDOW_SCALE, PLAYER_SIZE * WINDOW_SCALE, SDL_PIXELFORMAT_RGBA32);
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    float radius = PLAYER_SIZE * WINDOW_SCALE * 0.5f;
    float diameter = radius * 2.0f;
    float x = radius - 1.0f, y = 0.0f;
    float tx = 1.0f, ty = 1.0f;
    float error = tx - diameter;

    while (x >= y) {
        SDL_RenderPoint(renderer, radius + x, radius - y);
        SDL_RenderPoint(renderer, radius + x, radius + y);
        SDL_RenderPoint(renderer, radius - x, radius - y);
        SDL_RenderPoint(renderer, radius - x, radius + y);
        SDL_RenderPoint(renderer, radius + y, radius - x);
        SDL_RenderPoint(renderer, radius + y, radius + x);
        SDL_RenderPoint(renderer, radius - y, radius - x);
        SDL_RenderPoint(renderer, radius - y, radius + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        } else {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    SDL_RenderLine(renderer, radius, radius,
        radius + SDL_cosf(player->direction) * 100,
        radius + SDL_sinf(player->direction) * 100);
    
    SDL_RenderPresent(renderer);
    player->texture = Camera_CreateTextureFromSurface(surface);

    SDL_DestroyRenderer(renderer);
    SDL_DestroySurface(surface);

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
    SDL_DestroyTexture(player->texture);
    free(player);
}
