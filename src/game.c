#include <display.h>
#include <game.h>
#include <player.h>


void run_game() {
    Player *player = create_player();

    SDL_Event event;
    bool is_running = true;
    while (is_running) {
        // Check events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
        }

        // Update screen
        SDL_SetRenderDrawColor(app.renderer, WINDOW_BACKGROUND.r,
            WINDOW_BACKGROUND.g, WINDOW_BACKGROUND.b, WINDOW_BACKGROUND.a);
        SDL_RenderClear(app.renderer);

        SDL_RenderCopy(app.renderer, player->texture, NULL, player->rect);

        SDL_RenderPresent(app.renderer);
    }

    destroy_player(player);
}
