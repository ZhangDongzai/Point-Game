#ifndef INCLUDE_INFOLABEL_H
#define INCLUDE_INFOLABEL_H

#include <SDL3_ttf/SDL_ttf.h>
#include <player.h>
#include <camera.h>
#include <common.h>

/**
 * The info label object
 */
typedef struct {
	TTF_Font *font;
	char text[10];
	SDL_Surface *surface;
	SDL_Renderer *renderer;
	TTF_TextEngine *textEngine;
	Render_Object *object;
} InfoLabel;

/**
 * Create an info label
 *
 * \returns The info label object
 */
InfoLabel *InfoLabel_Create();

/**
 * Update info
 *
 * \param infoLabel The info label object
 */
void InfoLabel_Update(InfoLabel *infoLabel, Player *player);

/**
 * Delete an info label
 *
 * \param infoLabel The info label object
 */
void InfoLabel_Delete(InfoLabel *infoLabel);

#endif