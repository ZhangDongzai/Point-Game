#include <ui.h>

UI UI_Init(SDL_Renderer *renderer, TTF_Font *font)
{
	UI ui;
	ui.mode = UI_MODE_START;
	ui.rect = (SDL_Rect){ 0, 0, 0, 0 };
	ui.edgeColor = UI_DEFAULT_EDGE_COLOR;
	ui.bgColor = UI_DEFAULT_BG_COLOR;
	ui.fontColor = UI_DEFAULT_FONT_COLOR;

	ui.renderer = renderer;
	ui.font = font;
	ui.textEngine = TTF_CreateRendererTextEngine(renderer);
	ui.text = TTF_CreateText(ui.textEngine, ui.font, "", strlen(""));
	return ui;
}

void UI_RenderStart(UI *ui)
{
	UI_Reset(ui);
	ui->rect.x = UI_START_TITLE_POS.x * WINDOW_SCALE;
	ui->rect.y = UI_START_TITLE_POS.y * WINDOW_SCALE;
	UI_Label(ui, WINDOW_NAME);

	UI_Reset(ui);
	ui->rect.x = UI_START_BUTTON_POS.x * WINDOW_SCALE;
	ui->rect.y = UI_START_BUTTON_POS.y * WINDOW_SCALE;
	if (UI_Button(ui, "START"))
		ui->mode = UI_MODE_GAME;
}

void UI_RenderGame(UI *ui, Player *player)
{
	SDL_FPoint pos = { player->object.rect.x + PLAYER_SIZE * 2,
			   player->object.rect.y + PLAYER_SIZE * 1.5f };
	pos = Camera_GetPosOnScreen(&pos);

	char text[8];
	if (SDL_GetTicks() - player->magazine.prevReloadTime <
	    BULLET_RELOAD_TIME_MS)
		sprintf(text, "  /%02d", BULLET_MAX_COUNT % 100);
	else
		sprintf(text, "%02d/%02d", player->magazine.bulletNumber % 100,
			BULLET_MAX_COUNT % 100);

	UI_Reset(ui);
	ui->rect.x = pos.x, ui->rect.y = pos.y;
	ui->bgColor = UI_INFOLABEL_BACKGROUND_COLOR;
	ui->edgeColor = COLOR_ZERO;
	TTF_SetFontSize(ui->font, UI_INFOLABEL_FONT_SIZE);
	UI_Label(ui, text);

	const bool *keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		ui->mode = UI_MODE_MENU;
	}
}

void UI_RenderMenu(UI *ui)
{
	UI_Reset(ui);
	ui->rect.x = UI_MENU_BUTTON_POS.x * WINDOW_SCALE;
	ui->rect.y = UI_MENU_BUTTON_POS.y * WINDOW_SCALE;
	if (UI_Button(ui, "CONTINUE"))
		ui->mode = UI_MODE_GAME;
}

void UI_Destroy(UI *ui)
{
	TTF_DestroyText(ui->text);
	TTF_DestroyRendererTextEngine(ui->textEngine);
}

bool UI_Button(UI *ui, char *text)
{
	UI_Label(ui, text);

	SDL_FPoint fMouse;
	SDL_MouseButtonFlags mouseFlag =
		SDL_GetMouseState(&fMouse.x, &fMouse.y);
	SDL_Point mouse = { fMouse.x, fMouse.y };
	if (SDL_PointInRect(&mouse, &ui->rect)) {
		SDL_RenderLine(ui->renderer, ui->rect.x,
			       ui->rect.y + ui->rect.h, ui->rect.x + ui->rect.w,
			       ui->rect.y + ui->rect.h);
		if (mouseFlag & SDL_BUTTON_LMASK)
			return true;
	}
	return false;
}

void UI_Label(UI *ui, char *text)
{
	SDL_FRect rect;
	int pad = TTF_GetFontSize(ui->font) / 4;

	TTF_SetTextString(ui->text, text, strlen(text));
	TTF_GetTextSize(ui->text, &ui->rect.w, &ui->rect.h);
	ui->rect.x -= ui->rect.w / 2.0f;
	ui->rect.y -= ui->rect.h / 2.0f;
	SDL_RectToFRect(&ui->rect, &rect);
	rect.x -= pad, rect.y -= pad;
	rect.w += pad * 2, rect.h += pad * 2;

	if (ui->bgColor.a) {
		SDL_SetRenderDrawColor(ui->renderer, ui->bgColor.r,
				       ui->bgColor.g, ui->bgColor.b,
				       ui->bgColor.a);
		SDL_RenderFillRect(ui->renderer, &rect);
	}

	SDL_SetRenderDrawColor(ui->renderer, ui->fontColor.r, ui->fontColor.g,
			       ui->fontColor.b, ui->fontColor.a);
	TTF_DrawRendererText(ui->text, ui->rect.x, ui->rect.y);

	if (ui->edgeColor.a) {
		SDL_SetRenderDrawColor(ui->renderer, ui->edgeColor.r,
				       ui->edgeColor.g, ui->edgeColor.b,
				       ui->edgeColor.a);
		SDL_RenderRect(ui->renderer, &rect);
	}
}

void UI_Reset(UI *ui)
{
	ui->rect = (SDL_Rect){ 0, 0, 0, 0 };
	ui->edgeColor = UI_DEFAULT_EDGE_COLOR;
	ui->bgColor = UI_DEFAULT_BG_COLOR;
	ui->fontColor = UI_DEFAULT_FONT_COLOR;
}