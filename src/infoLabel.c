#include <infoLabel.h>

InfoLabel *InfoLabel_Create()
{
	InfoLabel *infoLabel = (InfoLabel *)calloc(1, sizeof(InfoLabel));
	infoLabel->font = TTF_OpenFont(INFOLABEL_FONT, INFOLABEL_FONT_SIZE);
	strcpy(infoLabel->text, "00");
	infoLabel->object = (Render_Object *)calloc(1, sizeof(Render_Object));
	infoLabel->object->direction = 0.0f;
	infoLabel->object->rect.h = 1.0f;

	return infoLabel;
}

void InfoLabel_Update(InfoLabel *infoLabel, Player *player)
{
	sprintf(infoLabel->text, "%d/%d", player->bulletNumber, BULLET_MAX_COUNT);
	infoLabel->object->rect.x = player->object->rect.x + 1;
	infoLabel->object->rect.y = player->object->rect.y + 1;
	infoLabel->object->rect.w = strlen(infoLabel->text) * 0.4f;

	infoLabel->object->texture =
		Painter_DrawInfoLabel(infoLabel->text, infoLabel->font,
				      strlen(infoLabel->text), INFOLABEL_COLOR);
}

void InfoLabel_Delete(InfoLabel *infoLabel)
{
	SDL_DestroyTexture(infoLabel->object->texture);
	free(infoLabel->object);
	free(infoLabel);
}