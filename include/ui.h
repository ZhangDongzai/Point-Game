#ifndef INCLUDE_UI_H
#define INCLUDE_UI_H

#include <player.h>
#include <common.h>

typedef enum {
	UI_MODE_GAME,
	UI_MODE_MENU,
	UI_MODE_START,
} UI_MODE;

typedef struct {
	UI_MODE mode;
	TTF_Font *font;
	TTF_TextEngine *textEngine;
	TTF_Text *text;
} UI;

typedef struct {
	SDL_Rect rect;
	SDL_Color bgColor;

	/* Text */
	char text[16];
	SDL_Color textColor;
	float textFontSize;
} UI_Button;

/** 
 * Initialize UI
 */
UI UI_Init(SDL_Renderer *renderer, TTF_Font *font);

/**
 * Render welcome screen
 */
void UI_RenderStart(SDL_Renderer *renderer, UI *ui);

/**
 * Render infomation in game
 */
void UI_RenderGame(SDL_Renderer *renderer, UI *ui, Player *player);

/**
 * Render menu when game stops
 */
void UI_RenderMenu(SDL_Renderer *renderer, UI *ui);

/**
 * Destroy UI
 */
void UI_Destroy(UI *ui);

/** Create a button
 *
 * \param ui the UI object
 * \param bgColor the color of button's background
 * \param text the text of the button (length < 16)
 * \param textColor the color of the text
 * \param textFontSize the ptsize of text's font
 * \param x the x of button's center pos
 * \param y the y of buttob's center pos
 *
 * \return the button object
 */
UI_Button UI_CreateButton(UI *ui, SDL_Color *bgColor, char *text,
			   SDL_Color *textColor, float textFontSize, int x,
			   int y);

/** Render a button
 *
 * \param renderer the SDL_Renderer object
 * \param ui the UI object
 * \param button the button object
 *
 * \return true if button is clicked, false otherwise
 */
bool UI_RenderButton(SDL_Renderer *renderer, UI *ui, UI_Button *button);

#endif /* INCLUDE_UI_H */