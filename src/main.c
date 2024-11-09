#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>


int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Point Game", 1280, 720, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    SDL_FRect rect = {100, 100, 100, 100};
    const int FPS_Time = 1000 / 60;
    Uint32 _FPS_Timer;

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderLine(renderer, 0, 0, 1280, 720);
        SDL_RenderRect(renderer, &rect);

        SDL_RenderPresent(renderer);

        if (SDL_GetTicks() - _FPS_Timer < FPS_Time) {
            SDL_Delay(FPS_Time - SDL_GetTicks() + _FPS_Timer);
        }
        _FPS_Timer = SDL_GetTicks();
    }
    

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
