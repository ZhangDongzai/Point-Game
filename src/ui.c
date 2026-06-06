#include <ui.h>

UI UI_Init(SDL_Renderer *renderer, TTF_Font *font)
{
	UI ui;
	ui.mode = UI_MODE_START;
	ui.rect = (SDL_FRect){ 0, 0, 0, 0 };
	ui.edgeColor = UI_DEFAULT_EDGE_COLOR;
	ui.bgColor = UI_DEFAULT_BG_COLOR;
	ui.fontColor = UI_DEFAULT_FONT_COLOR;

	ui.renderer = renderer;
	ui.font = font;
	ui.textEngine = TTF_CreateRendererTextEngine(renderer);
	ui.text = TTF_CreateText(ui.textEngine, ui.font, "", strlen(""));
	return ui;
}

void UI_Destroy(UI *ui)
{
	TTF_DestroyText(ui->text);
	TTF_DestroyRendererTextEngine(ui->textEngine);
}

bool UI_Button(UI *ui, char *text)
{
	UI_Label(ui, text);

	SDL_FPoint mouse;
	SDL_MouseButtonFlags mouseFlag = SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRectFloat(&mouse, &ui->rect)) {
		SDL_RenderLine(ui->renderer, ui->rect.x + ui->pad,
			       ui->rect.y + ui->rect.h - ui->pad,
			       ui->rect.x + ui->rect.w - ui->pad,
			       ui->rect.y + ui->rect.h - ui->pad);
		if (mouseFlag & SDL_BUTTON_LMASK)
			return true;
	}
	return false;
}

void UI_Label(UI *ui, char *text)
{
	int w, h;
	ui->pad = TTF_GetFontSize(ui->font) / 4;

	TTF_SetTextString(ui->text, text, strlen(text));
	TTF_GetTextSize(ui->text, &w, &h);
	ui->rect.x -= w / 2.0f + ui->pad;
	ui->rect.y -= h / 2.0f + ui->pad;
	ui->rect.w = w + ui->pad * 2;
	ui->rect.h = h + ui->pad * 2;

	UI_Frame(ui);

	Camera_SetRenderDrawColor(ui->renderer, &ui->fontColor);
	TTF_DrawRendererText(ui->text, ui->rect.x + ui->pad,
			     ui->rect.y + ui->pad);
}

void UI_Frame(UI *ui)
{
	if (ui->bgColor.a) {
		Camera_SetRenderDrawColor(ui->renderer, &ui->bgColor);
		SDL_RenderFillRect(ui->renderer, &ui->rect);
	}

	if (ui->edgeColor.a) {
		Camera_SetRenderDrawColor(ui->renderer, &ui->edgeColor);
		SDL_RenderRect(ui->renderer, &ui->rect);
	}
}

void UI_Reset(UI *ui)
{
	ui->rect = (SDL_FRect){ 0, 0, 0, 0 };
	ui->edgeColor = UI_DEFAULT_EDGE_COLOR;
	ui->bgColor = UI_DEFAULT_BG_COLOR;
	ui->fontColor = UI_DEFAULT_FONT_COLOR;
	TTF_SetFontSize(ui->font, UI_DEFAULT_FONT_SIZE);
}