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
} UI;

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

#endif /* INCLUDE_UI_H */