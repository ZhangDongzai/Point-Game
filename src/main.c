#include <main.h>

App app;


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    app.window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    app.renderer = SDL_CreateRenderer(app.window, -1, 0);
    app.keyBoardState = SDL_GetKeyboardState(NULL);
    Player *player = createPlayer(640, 360, PLAYER_COLOR);
    Map map = loadMap();

    Uint32 lastFrameTime = 0;
    const short frameTime = 1000 / WINDOW_FPS;
    unsigned int deltaTimeMs = 0;

    bool isRunning = true;
    while (isRunning) {
        // Check events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Update
        updatePlayer(player, deltaTimeMs, map);

        // Render
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
        SDL_RenderClear(app.renderer);
        renderMap(app.renderer, map);
        renderRaycast(app.renderer, player, map);
        renderPlayer(app.renderer, player);
        SDL_RenderPresent(app.renderer);

        // Control fps
        deltaTimeMs = SDL_GetTicks() - lastFrameTime;
        if (frameTime > deltaTimeMs) {
            SDL_Delay(frameTime - deltaTimeMs);
            deltaTimeMs = frameTime;
        }
        lastFrameTime = SDL_GetTicks();
    }

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    return 0;
}
