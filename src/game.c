#include <display.h>
#include <game.h>
#include <player.h>


void run_game() {
    Player *player = CreatePlayer();

    SDL_Event event;
    bool is_running = true;
    Uint64 current_delta_time_ms = 0;
    Uint64 last_delta_time_ms = 0;
    while (is_running) {
        // Check events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
        }

        // Update data
        current_delta_time_ms = SDL_GetTicks64();
        app.delta_time_s = (current_delta_time_ms - last_delta_time_ms) / 1000.0f;
        last_delta_time_ms = current_delta_time_ms;
        UpdatePlayer(player);

        // Update screen
        SDL_SetRenderDrawColor(app.renderer, WINDOW_BACKGROUND.r,
            WINDOW_BACKGROUND.g, WINDOW_BACKGROUND.b, WINDOW_BACKGROUND.a);
        SDL_RenderClear(app.renderer);

        SDL_RenderCopy(app.renderer, player->texture, NULL, player->rect);

        SDL_RenderPresent(app.renderer);
    }

    DestroyPlayer(player);
}
