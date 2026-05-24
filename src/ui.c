#include <ui.h>

UI UI_Init(SDL_Renderer *renderer, TTF_Font *font)
{
	return (UI){ UI_MODE_START, font,
		     TTF_CreateRendererTextEngine(renderer) };
}

void UI_RenderStart(SDL_Renderer *renderer, UI *ui)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// Title
	TTF_SetFontSize(ui->font, WINDOW_SCALE * 2);
	TTF_Text *text = TTF_CreateText(ui->textEngine, ui->font,
					UI_START_TITLE_TEXT,
					strlen(UI_START_TITLE_TEXT));
	SDL_Rect rect;
	TTF_GetTextSize(text, &rect.w, &rect.h);
	rect.x = UI_START_TITLE_POS.x * WINDOW_SCALE - rect.w / 2.0f;
	rect.y = UI_START_TITLE_POS.y * WINDOW_SCALE - rect.h / 2.0f;
	TTF_DrawRendererText(text, rect.x, rect.y);

	// Button
	TTF_SetFontSize(ui->font, WINDOW_SCALE);
	TTF_SetTextString(text, UI_START_BUTTON_TEXT,
			  strlen(UI_START_BUTTON_TEXT));
	TTF_GetTextSize(text, &rect.w, &rect.h);
	rect.x = UI_START_BUTTON_POS.x * WINDOW_SCALE - rect.w / 2.0f;
	rect.y = UI_START_BUTTON_POS.y * WINDOW_SCALE - rect.h / 2.0f;
	TTF_DrawRendererText(text, rect.x, rect.y);
	TTF_DestroyText(text);

	SDL_FPoint mouse;
	SDL_MouseButtonFlags mouseFlag = SDL_GetMouseState(&mouse.x, &mouse.y);
	SDL_Point mousef = { mouse.x, mouse.y };
	if (SDL_PointInRect(&mousef, &rect)) {
		SDL_RenderLine(renderer, rect.x, rect.y + rect.h,
			       rect.x + rect.w, rect.y + rect.h);
		if (mouseFlag & SDL_BUTTON_LMASK)
			ui->mode = UI_MODE_GAME;
	}
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
	TTF_Text *renderText =
		TTF_CreateText(ui->textEngine, ui->font, text, strlen(text));
	TTF_DrawRendererText(renderText, pos.x + textOffset,
			     pos.y + textOffset);
	TTF_DestroyText(renderText);

	const bool *keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		ui->mode = UI_MODE_MENU;
	}
}

void UI_RenderMenu(SDL_Renderer *renderer, UI *ui)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	TTF_Text *text = TTF_CreateText(ui->textEngine, ui->font,
					      UI_MENU_BUTTON_TEXT,
					      strlen(UI_MENU_BUTTON_TEXT));
	SDL_Rect rect;
	TTF_GetTextSize(text, &rect.w, &rect.h);
	rect.x = UI_MENU_BUTTON_POS.x * WINDOW_SCALE - rect.w / 2.0f;
	rect.y = UI_MENU_BUTTON_POS.y * WINDOW_SCALE - rect.h / 2.0f;
	TTF_DrawRendererText(text, rect.x, rect.y);
	TTF_DestroyText(text);

	SDL_FPoint mouse;
	SDL_MouseButtonFlags mouseFlag = SDL_GetMouseState(&mouse.x, &mouse.y);
	SDL_Point mousef = { mouse.x, mouse.y };
	if (SDL_PointInRect(&mousef, &rect)) {
		SDL_RenderLine(renderer, rect.x, rect.y + rect.h,
			       rect.x + rect.w, rect.y + rect.h);
		if (mouseFlag & SDL_BUTTON_LMASK)
			ui->mode = UI_MODE_GAME;
	}
}

void UI_Destroy(UI *ui)
{
	TTF_DestroyRendererTextEngine(ui->textEngine);
}