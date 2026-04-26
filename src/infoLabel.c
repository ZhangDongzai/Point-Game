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
	infoLabel->object->rect.x = player->object->rect.x + PLAYER_SIZE;
	infoLabel->object->rect.y = player->object->rect.y + PLAYER_SIZE;

	if (SDL_GetTicks() - player->magazine.prevReloadTime <
	    BULLET_RELOAD_TIME_MS)
		sprintf(infoLabel->text, "  /%d", BULLET_MAX_COUNT);
	else
		sprintf(infoLabel->text, "%02d/%d",
			player->magazine.bulletNumber, BULLET_MAX_COUNT);

	SDL_Surface *surface =
		SDL_CreateSurface(infoLabel->object->rect.w * WINDOW_SCALE,
				  infoLabel->object->rect.h * WINDOW_SCALE,
				  SDL_PIXELFORMAT_RGBA32);
	SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);

	TTF_TextEngine *textEngine = TTF_CreateRendererTextEngine(renderer);
	TTF_Text *text = TTF_CreateText(textEngine, infoLabel->font,
					infoLabel->text,
					strlen(infoLabel->text));

	SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	TTF_DrawRendererText(text, (int)(WINDOW_SCALE / 20.0f),
			     (int)(WINDOW_SCALE / 20.0f));
	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(infoLabel->object->texture);
	infoLabel->object->texture = Camera_CreateTextureFromSurface(surface);
	SDL_SetTextureBlendMode(infoLabel->object->texture,
				SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(infoLabel->object->texture, 200);

	TTF_DestroyText(text);
	TTF_DestroySurfaceTextEngine(textEngine);
	SDL_DestroyRenderer(renderer);
	SDL_DestroySurface(surface);
}

void InfoLabel_Delete(InfoLabel *infoLabel)
{
	SDL_DestroyTexture(infoLabel->object->texture);
	free(infoLabel->object);
	free(infoLabel);
}