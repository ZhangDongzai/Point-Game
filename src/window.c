#include <window.h>


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    App *app = (App *)malloc(sizeof(App));
    *appstate = app;

    SDL_SetAppMetadata(WINDOW_NAME, "1.0", "com.point-game.zhangdongzai");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
         &app->window, &app->renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    Camera_BindRenderer(app->renderer);

    app->player = Player_Create();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    App *app = appstate;

    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
    Camera_RenderObject(Player_GetRenderObject(app->player));
    
    SDL_RenderPresent(app->renderer);

    return SDL_APP_CONTINUE; 
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    free(appstate);
    return;
}
