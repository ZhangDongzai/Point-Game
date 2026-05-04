#include <infoLabel.h>

InfoLabel InfoLabel_Create()
{
	InfoLabel infoLabel;
	strcpy(infoLabel.text, "00");

	infoLabel.object.direction = 0.0f;
	infoLabel.object.rect.h = 1.0f;
	infoLabel.object.rect.w = 2.0f;

	infoLabel.surface = SDL_CreateSurface(
		infoLabel.object.rect.w * WINDOW_SCALE,
		infoLabel.object.rect.h * WINDOW_SCALE, RENDER_PIXEL_FORMAT);
	infoLabel.object.texture =
		Camera_CreateTextureFromSurface(infoLabel.surface);
	SDL_SetTextureBlendMode(infoLabel.object.texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(infoLabel.object.texture, 200);

	infoLabel.renderer = SDL_CreateSoftwareRenderer(infoLabel.surface);
	infoLabel.textEngine = TTF_CreateRendererTextEngine(infoLabel.renderer);
	infoLabel.font = TTF_OpenFont(INFOLABEL_FONT, INFOLABEL_FONT_SIZE);

	return infoLabel;
}

void InfoLabel_Update(InfoLabel *infoLabel, Player *player)
{
	infoLabel->object.rect.x = player->object.rect.x + PLAYER_SIZE;
	infoLabel->object.rect.y = player->object.rect.y + PLAYER_SIZE;

	if (SDL_GetTicks() - player->magazine.prevReloadTime <
	    BULLET_RELOAD_TIME_MS)
		sprintf(infoLabel->text, "  /%d", BULLET_MAX_COUNT);
	else
		sprintf(infoLabel->text, "%02d/%d",
			player->magazine.bulletNumber, BULLET_MAX_COUNT);

	TTF_Text *text = TTF_CreateText(infoLabel->textEngine, infoLabel->font,
					infoLabel->text,
					strlen(infoLabel->text));

	SDL_SetRenderDrawColor(infoLabel->renderer, 150, 150, 150, 255);
	SDL_RenderClear(infoLabel->renderer);
	SDL_SetRenderDrawColor(infoLabel->renderer, 255, 255, 255, 255);
	TTF_DrawRendererText(text, (int)(WINDOW_SCALE / 20.0f),
			     (int)(WINDOW_SCALE / 20.0f));
	SDL_RenderPresent(infoLabel->renderer);

	SDL_UpdateTexture(infoLabel->object.texture, NULL,
			  infoLabel->surface->pixels,
			  infoLabel->surface->pitch);

	TTF_DestroyText(text);
}

void InfoLabel_Delete(InfoLabel *infoLabel)
{
	TTF_CloseFont(infoLabel->font);
	TTF_DestroySurfaceTextEngine(infoLabel->textEngine);
	SDL_DestroyRenderer(infoLabel->renderer);
	SDL_DestroySurface(infoLabel->surface);
	SDL_DestroyTexture(infoLabel->object.texture);
}