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

	if (!SDL_CreateWindowAndRenderer(WINDOW_NAME, WINDOW_WIDTH,
					 WINDOW_HEIGHT, SDL_WINDOW_OPENGL,
					 &app->window, &app->renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!TTF_Init()) {
		SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	app->font = TTF_OpenFont(WINDOW_FONT_PATH, WINDOW_SCALE);
	if (!app->font) {
		SDL_Log("Couldn't load font file: %s\n\tFont file path: %s\n",
			SDL_GetError(), WINDOW_FONT_PATH);
		return SDL_APP_FAILURE;
	}

	Camera_BindRenderer(app->renderer);

	app->map = Map_Init();
	app->bulletList = Bullet_CreateList();
	app->player = Player_Create(app->renderer, app->bulletList);
	app->ui = UI_Init(app->renderer, app->font);

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

	SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
	SDL_RenderClear(app->renderer);

	switch (app->ui.mode) {
	case UI_MODE_GAME:
		Bullet_UpdateList(app->bulletList, app->deltaTime, &app->map);
		Player_Update(&app->player, app->deltaTime, app->bulletList,
			      &app->map);
		Camera_Update(&app->player.object, &app->map.boundary);

		SDL_FPoint start = { 0.0f, 0.0f };
		start = Camera_GetPosOnMap(&start);
		start.x = (int)start.x, start.y = (int)start.y;
		for (int row = 0; row < WINDOW_HEIGHT_SCALE + 1;
		     row++, start.y++) {
			Map_Render(app->renderer, &app->map, &start);

			Camera_RenderObjects(app->bulletList, start.y);
			Camera_RenderObject(&app->player.object, start.y);
		}

		Player_DrawSight(app->renderer, &app->player, &app->map);

		char labelText[8];
		if (SDL_GetTicks() - app->player.magazine.prevReloadTime <
		    BULLET_RELOAD_TIME_MS)
			sprintf(labelText, "  /%02d", BULLET_MAX_COUNT % 100);
		else
			sprintf(labelText, "%02d/%02d",
				app->player.magazine.bulletNumber % 100,
				BULLET_MAX_COUNT % 100);

		UI_Reset(&app->ui);
		app->ui.rect.x = WINDOW_SCALE * 2;
		app->ui.rect.y = WINDOW_HEIGHT - WINDOW_SCALE;
		app->ui.edgeColor = COLOR_ZERO;
		TTF_SetFontSize(app->ui.font, UI_INFOLABEL_FONT_SIZE);
		UI_Label(&app->ui, labelText);

		const bool *keyboardState = SDL_GetKeyboardState(NULL);
		if (keyboardState[SDL_SCANCODE_ESCAPE]) {
			app->ui.mode = UI_MODE_MENU;
		}

		break;
	case UI_MODE_MENU:
		UI_Reset(&app->ui);
		app->ui.rect.x = UI_MENU_BUTTON_POS.x * WINDOW_SCALE;
		app->ui.rect.y = UI_MENU_BUTTON_POS.y * WINDOW_SCALE;
		if (UI_Button(&app->ui, "CONTINUE"))
			app->ui.mode = UI_MODE_GAME;
		break;
	case UI_MODE_START:
		UI_Reset(&app->ui);
		TTF_SetFontSize(app->ui.font, WINDOW_SCALE * 2);
		app->ui.rect.x = UI_START_TITLE_POS.x * WINDOW_SCALE;
		app->ui.rect.y = UI_START_TITLE_POS.y * WINDOW_SCALE;
		app->ui.edgeColor = COLOR_ZERO;
		UI_Label(&app->ui, WINDOW_NAME);

		UI_Reset(&app->ui);
		app->ui.rect.x = UI_START_BUTTON_POS.x * WINDOW_SCALE;
		app->ui.rect.y = UI_START_BUTTON_POS.y * WINDOW_SCALE;
		app->ui.edgeColor = COLOR_ZERO;
		if (UI_Button(&app->ui, "START"))
			app->ui.mode = UI_MODE_GAME;
		break;
	}
	SDL_RenderPresent(app->renderer);

	app->deltaTime = SDL_GetTicks() - app->preFrameTime;
	app->preFrameTime += app->deltaTime;

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	App *app = appstate;
	Bullet_DeleteList(app->bulletList);
	Player_Delete(&app->player);
	Map_Delete(&app->map);
	UI_Destroy(&app->ui);
	free(appstate);
	TTF_Quit();
	return;
}
