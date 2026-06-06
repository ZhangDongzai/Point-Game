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
	SDL_FRect rect;
	SDL_Color edgeColor;
	SDL_Color bgColor;
	SDL_Color fontColor;
	int pad;

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
 * Destroy UI
 */
void UI_Destroy(UI *ui);

/** Render a button
 *
 * \param ui the UI object
 * \param text the text on the button
 *
 * \return true if button is clicked, false otherwise
 */
bool UI_Button(UI *ui, char *text);

/** Render a label
 * 
 * \param ui the UI object
 * \param text the text on the label
 */
void UI_Label(UI *ui, char *text);

/** Render a frame
 *
 * \param ui the UI object
 */
void UI_Frame(UI *ui);

/** Set all UI elements to default values
 *
 * \param ui the UI object
 */
void UI_Reset(UI *ui);

#endif /* INCLUDE_UI_H */