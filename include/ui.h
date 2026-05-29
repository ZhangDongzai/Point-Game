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
	SDL_Renderer *renderer;
	TTF_Font *font;
	TTF_TextEngine *textEngine;
	TTF_Text *text;
} UI;

/** 
 * Initialize UI
 */
UI UI_Init(SDL_Renderer *renderer, TTF_Font *font);

/**
 * Render welcome screen
 */
void UI_RenderStart(UI *ui);

/**
 * Render infomation in game
 */
void UI_RenderGame(UI *ui, Player *player);

/**
 * Render menu when game stops
 */
void UI_RenderMenu(UI *ui);

/**
 * Destroy UI
 */
void UI_Destroy(UI *ui);

/** Render a button
 *
 * \param ui the UI object
 * \param text the text on the button
 * \param x the x of button's center pos
 * \param y the y of button's center pos
 *
 * \return true if button is clicked, false otherwise
 */
bool UI_Button(UI *ui, char *text, int x, int y);

#endif /* INCLUDE_UI_H */