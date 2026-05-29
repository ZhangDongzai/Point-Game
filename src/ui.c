#include <ui.h>

UI UI_Init(SDL_Renderer *renderer, TTF_Font *font)
{
	UI ui;
	ui.mode = UI_MODE_START;
	ui.renderer = renderer;
	ui.font = font;
	ui.textEngine = TTF_CreateRendererTextEngine(renderer);
	ui.text = TTF_CreateText(ui.textEngine, ui.font, "", strlen(""));
	return ui;
}

void UI_RenderStart(UI *ui)
{
	SDL_SetRenderDrawColor(ui->renderer, 255, 255, 255, 255);
	// Title
	TTF_SetFontSize(ui->font, WINDOW_SCALE * 2);
	TTF_SetTextString(ui->text, UI_START_TITLE_TEXT,
			  sizeof(UI_START_TITLE_TEXT));
	SDL_Rect rect;
	TTF_GetTextSize(ui->text, &rect.w, &rect.h);
	rect.x = UI_START_TITLE_POS.x * WINDOW_SCALE - rect.w / 2.0f;
	rect.y = UI_START_TITLE_POS.y * WINDOW_SCALE - rect.h / 2.0f;
	TTF_DrawRendererText(ui->text, rect.x, rect.y);

	// Button
	if (UI_Button(ui, UI_START_BUTTON_TEXT,
		      UI_START_BUTTON_POS.x * WINDOW_SCALE,
		      UI_START_BUTTON_POS.y * WINDOW_SCALE))
		ui->mode = UI_MODE_GAME;
}

void UI_RenderGame(UI *ui, Player *player)
{
	SDL_FPoint pos = { player->object.rect.x + PLAYER_SIZE,
			   player->object.rect.y + PLAYER_SIZE };
	pos = Camera_GetPosOnScreen(&pos);
	SDL_FRect rect = { pos.x, pos.y, UI_INFOLABEL_WIDTH * WINDOW_SCALE,
			   UI_INFOLABEL_HEIGHT * WINDOW_SCALE };

	SDL_SetRenderDrawColor(ui->renderer, UI_INFOLABEL_BACKGROUND_COLOR.r,
			       UI_INFOLABEL_BACKGROUND_COLOR.g,
			       UI_INFOLABEL_BACKGROUND_COLOR.b,
			       UI_INFOLABEL_BACKGROUND_COLOR.a);
	SDL_RenderFillRect(ui->renderer, &rect);

	char text[8];
	int textOffset = WINDOW_SCALE / 20.0f;
	if (SDL_GetTicks() - player->magazine.prevReloadTime <
	    BULLET_RELOAD_TIME_MS)
		sprintf(text, "  /%02d", BULLET_MAX_COUNT % 100);
	else
		sprintf(text, "%02d/%02d", player->magazine.bulletNumber % 100,
			BULLET_MAX_COUNT % 100);
	SDL_SetRenderDrawColor(ui->renderer, UI_INFOLABEL_FONT_COLOR.r,
			       UI_INFOLABEL_FONT_COLOR.g,
			       UI_INFOLABEL_FONT_COLOR.b,
			       UI_INFOLABEL_FONT_COLOR.a);
	TTF_SetFontSize(ui->font, UI_INFOLABEL_FONT_SIZE);
	TTF_SetTextString(ui->text, text, strlen(text));
	TTF_DrawRendererText(ui->text, pos.x + textOffset, pos.y + textOffset);

	const bool *keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		ui->mode = UI_MODE_MENU;
	}
}

void UI_RenderMenu(UI *ui)
{
	if (UI_Button(ui, UI_MENU_BUTTON_TEXT,
		      UI_MENU_BUTTON_POS.x * WINDOW_SCALE,
		      UI_MENU_BUTTON_POS.y * WINDOW_SCALE))
		ui->mode = UI_MODE_GAME;
}

void UI_Destroy(UI *ui)
{
	TTF_DestroyText(ui->text);
	TTF_DestroyRendererTextEngine(ui->textEngine);
}

bool UI_Button(UI *ui, char *text, int x, int y)
{
	SDL_Rect rect;

	TTF_SetTextString(ui->text, text, strlen(text));
	TTF_GetTextSize(ui->text, &rect.w, &rect.h);

	rect.x = x - rect.w / 2.0f;
	rect.y = y - rect.h / 2.0f;

	TTF_DrawRendererText(ui->text, rect.x, rect.y);

	SDL_FPoint fMouse;
	SDL_MouseButtonFlags mouseFlag =
		SDL_GetMouseState(&fMouse.x, &fMouse.y);
	SDL_Point mouse = { fMouse.x, fMouse.y };
	if (SDL_PointInRect(&mouse, &rect)) {
		SDL_RenderLine(ui->renderer, rect.x, rect.y + rect.h,
			       rect.x + rect.w, rect.y + rect.h);
		if (mouseFlag & SDL_BUTTON_LMASK)
			return true;
	}
	return false;
}