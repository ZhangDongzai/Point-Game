#include <window.h>

// NOTE: SDL_main is only in window.c
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
	App *app = *appstate = (App *)malloc(sizeof(App));

	SDL_SetAppMetadata(WINDOW_NAME, "1.0", "com.point-game.zhangdongzai");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!TTF_Init()) {
		SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer(WINDOW_NAME, WINDOW_WIDTH,
					 WINDOW_HEIGHT, 0, &app->window,
					 &app->renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	Camera_BindRenderer(app->renderer, PLAYER_DEFAULT_POS);

	app->bulletList = Bullet_CreateList();
	app->player = Player_Create(app->bulletList);
	app->map = Map_Init();
	app->infoLabel = InfoLabel_Create();

	app->preFrameTime = SDL_GetTicks();
	app->deltaTime = 0;

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	App *app = appstate;

	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	App *app = appstate;

	Bullet_UpdateList(app->bulletList, app->deltaTime, &app->map);
	Player_Update(&app->player, app->deltaTime, app->bulletList, &app->map);
	InfoLabel_Update(&app->infoLabel, &app->player);
	Map_Update(&app->map);
	Camera_Update(&app->player.object, Map_GetBoundary());

	SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
	SDL_RenderClear(app->renderer);

	Camera_RenderObject(&app->map.object);
	Player_DrawSight(app->renderer, &app->player, &app->map);
	Camera_RenderObjects(app->bulletList);
	Camera_RenderObject(&app->player.object);
	Camera_RenderObject(&app->infoLabel.object);

	SDL_RenderPresent(app->renderer);

	app->deltaTime = SDL_GetTicks() - app->preFrameTime;
	if (WINDOW_DELTA_TIME > app->deltaTime) {
		SDL_Delay(WINDOW_DELTA_TIME - app->deltaTime);
		app->deltaTime = WINDOW_DELTA_TIME;
	}
	app->preFrameTime = SDL_GetTicks();

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	App *app = appstate;
	Bullet_DeleteList(app->bulletList);
	Player_Delete(&app->player);
	Map_Delete(&app->map);
	InfoLabel_Delete(&app->infoLabel);
	free(appstate);
	TTF_Quit();
	return;
}
