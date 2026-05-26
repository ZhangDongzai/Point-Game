#include <ui.h>

UI UI_Init(SDL_Renderer *renderer, TTF_Font *font)
{
	UI ui;
	ui.font = font;
	ui.mode = UI_MODE_START;
	ui.textEngine = TTF_CreateRendererTextEngine(renderer);
	ui.text = TTF_CreateText(ui.textEngine, ui.font, "", strlen(""));
	return ui;
}

void UI_RenderStart(SDL_Renderer *renderer, UI *ui)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
	UI_Button button = UI_CreateButton(
		ui, NULL, UI_START_BUTTON_TEXT, &UI_DEFAULT_COLOR, WINDOW_SCALE,
		UI_START_BUTTON_POS.x * WINDOW_SCALE,
		UI_START_BUTTON_POS.y * WINDOW_SCALE);
	if (UI_RenderButton(renderer, ui, &button))
		ui->mode = UI_MODE_GAME;
}

void UI_RenderGame(SDL_Renderer *renderer, UI *ui, Player *player)
{
	SDL_FPoint pos = { player->object.rect.x + PLAYER_SIZE,
			   player->object.rect.y + PLAYER_SIZE };
	pos = Camera_GetPosOnScreen(&pos);
	SDL_FRect rect = { pos.x, pos.y, UI_INFOLABEL_WIDTH * WINDOW_SCALE,
			   UI_INFOLABEL_HEIGHT * WINDOW_SCALE };

	SDL_SetRenderDrawColor(renderer, UI_INFOLABEL_BACKGROUND_COLOR.r,
			       UI_INFOLABEL_BACKGROUND_COLOR.g,
			       UI_INFOLABEL_BACKGROUND_COLOR.b,
			       UI_INFOLABEL_BACKGROUND_COLOR.a);
	SDL_RenderFillRect(renderer, &rect);

	char text[8];
	int textOffset = WINDOW_SCALE / 20.0f;
	if (SDL_GetTicks() - player->magazine.prevReloadTime <
	    BULLET_RELOAD_TIME_MS)
		sprintf(text, "  /%02d", BULLET_MAX_COUNT % 100);
	else
		sprintf(text, "%02d/%02d", player->magazine.bulletNumber % 100,
			BULLET_MAX_COUNT % 100);
	SDL_SetRenderDrawColor(renderer, UI_INFOLABEL_FONT_COLOR.r,
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

void UI_RenderMenu(SDL_Renderer *renderer, UI *ui)
{
	UI_Button button = UI_CreateButton(ui, NULL, UI_MENU_BUTTON_TEXT,
					   &UI_DEFAULT_COLOR, WINDOW_SCALE,
					   UI_MENU_BUTTON_POS.x * WINDOW_SCALE,
					   UI_MENU_BUTTON_POS.y * WINDOW_SCALE);
	if (UI_RenderButton(renderer, ui, &button))
		ui->mode = UI_MODE_GAME;
}

void UI_Destroy(UI *ui)
{
	TTF_DestroyText(ui->text);
	TTF_DestroyRendererTextEngine(ui->textEngine);
}

UI_Button UI_CreateButton(UI *ui, SDL_Color *bgColor, char *text,
			  SDL_Color *textColor, float textFontSize, int x,
			  int y)
{
	UI_Button button;

	button.rect.x = x, button.rect.y = y;
	button.rect.w = button.rect.h = 0;
	button.bgColor = bgColor ? *bgColor : UI_DEFAULT_BACKGROUND_COLOR;

	strcpy(button.text, text);
	button.textFontSize = textFontSize;
	button.textColor = textColor ? *textColor : UI_DEFAULT_COLOR;

	return button;
}

bool UI_RenderButton(SDL_Renderer *renderer, UI *ui, UI_Button *button)
{
	SDL_SetRenderDrawColor(renderer, button->bgColor.r, button->bgColor.g,
			       button->bgColor.b, button->bgColor.a);

	TTF_SetFontSize(ui->font, button->textFontSize);
	TTF_SetTextString(ui->text, button->text, strlen(button->text));

	TTF_GetTextSize(ui->text, &button->rect.w, &button->rect.h);
	button->rect.x = button->rect.x - button->rect.w / 2.0f;
	button->rect.y = button->rect.y - button->rect.h / 2.0f;
	SDL_FRect rect = { button->rect.x, button->rect.y, button->rect.w,
			   button->rect.h };

	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, button->textColor.r,
			       button->textColor.g, button->textColor.b,
			       button->textColor.a);
	TTF_DrawRendererText(ui->text, button->rect.x, button->rect.y);

	SDL_FPoint mousef;
	SDL_MouseButtonFlags mouseFlag =
		SDL_GetMouseState(&mousef.x, &mousef.y);
	SDL_Point mouse = { mousef.x, mousef.y };
	if (SDL_PointInRect(&mouse, &button->rect)) {
		SDL_RenderLine(renderer, button->rect.x,
			       button->rect.y + button->rect.h,
			       button->rect.x + button->rect.w,
			       button->rect.y + button->rect.h);
		if (mouseFlag & SDL_BUTTON_LMASK)
			return true;
	}
	return false;
}