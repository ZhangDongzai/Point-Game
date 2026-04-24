#include <infoLabel.h>

InfoLabel *InfoLabel_Create()
{
	InfoLabel *infoLabel = (InfoLabel *)calloc(1, sizeof(InfoLabel));
	infoLabel->font = TTF_OpenFont(INFOLABEL_FONT, INFOLABEL_FONT_SIZE);
	strcpy(infoLabel->text, "00");
	infoLabel->object = (Render_Object *)calloc(1, sizeof(Render_Object));
	infoLabel->object->direction = 0.0f;
	infoLabel->object->rect.h = 1.0f;
	infoLabel->object->rect.w = 2.0f;

	return infoLabel;
}

void InfoLabel_Update(InfoLabel *infoLabel, Player *player)
{
	infoLabel->object->rect.x = player->object->rect.x + 1;
	infoLabel->object->rect.y = player->object->rect.y + 1;

	if (SDL_GetTicks() - player->magazine.prevReloadTime <
	    BULLET_RELOAD_TIME_MS)
		sprintf(infoLabel->text, "    /%d", BULLET_MAX_COUNT);
	else
		sprintf(infoLabel->text, "%02d/%d",
			player->magazine.bulletNumber, BULLET_MAX_COUNT);

	TTF_TextEngine *textEngine = TTF_CreateSurfaceTextEngine();
	TTF_Text *text = TTF_CreateText(textEngine, infoLabel->font,
					infoLabel->text,
					strlen(infoLabel->text));
	SDL_Surface *surface =
		SDL_CreateSurface(infoLabel->object->rect.w * WINDOW_SCALE,
				  infoLabel->object->rect.h * WINDOW_SCALE,
				  SDL_PIXELFORMAT_RGBA32);

	TTF_DrawSurfaceText(text, 0, 0, surface);

	SDL_DestroyTexture(infoLabel->object->texture);
	infoLabel->object->texture = Camera_CreateTextureFromSurface(surface);

	SDL_DestroySurface(surface);
	TTF_DestroyText(text);
	TTF_DestroySurfaceTextEngine(textEngine);
}

void InfoLabel_Delete(InfoLabel *infoLabel)
{
	SDL_DestroyTexture(infoLabel->object->texture);
	free(infoLabel->object);
	free(infoLabel);
}