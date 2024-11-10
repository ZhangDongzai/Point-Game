#include <main.h>


int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }

    const int FPS_Time = 1000 / MAX_FPS;
    int _FPS_Timer = 0;

    bool isRunning = true;
    while (isRunning)
    {
        // Check events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawFillCircle(renderer, 50, 640, 360);

        SDL_RenderPresent(renderer);

        // Control fps
        if (SDL_GetTicks() - _FPS_Timer < FPS_Time) {
            SDL_Delay(FPS_Time - SDL_GetTicks() + _FPS_Timer);
        }
        _FPS_Timer = SDL_GetTicks();
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
