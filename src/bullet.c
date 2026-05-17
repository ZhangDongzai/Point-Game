#include <bullet.h>

BulletList *Bullet_CreateList()
{
	return (BulletList *)calloc(1, sizeof(BulletList));
}

bool Bullet_Create(BulletMagazine *magazine, Render_Object *object,
		   float direction)
{
	Uint64 now = SDL_GetTicks();

	if (now - magazine->prevShootTime < BULLET_SHOOT_DELTA)
		return false;
	magazine->prevShootTime = now;

	if (now - magazine->prevReloadTime < BULLET_RELOAD_TIME_MS)
		return false;

	if (magazine->bulletNumber <= 0)
		return false;
	magazine->bulletNumber--;

	for (; magazine->bulletList->object.texture;
	     magazine->bulletList = magazine->bulletList->next) {
		if (!magazine->bulletList->next) {
			magazine->bulletList->next = Bullet_CreateList();
			magazine->bulletList->next->prev = magazine->bulletList;
		}
	}

	Bullet bullet;
	bullet.srcrect.x = bullet.srcrect.y = 0;
	bullet.srcrect.w = BULLET_WIDTH * WINDOW_SCALE;
	bullet.srcrect.h = BULLET_HEIGHT * WINDOW_SCALE;
	bullet.dstrect.x = object->dstrect.x + object->dstrect.w / 2.0f -
			   BULLET_WIDTH / 2.0f;
	bullet.dstrect.y = object->dstrect.y + object->dstrect.h / 2.0f -
			   BULLET_HEIGHT / 2.0f;
	bullet.dstrect.w = BULLET_WIDTH;
	bullet.dstrect.h = BULLET_HEIGHT;
	bullet.flipMode = SDL_FLIP_NONE;
	bullet.direction = direction;

	SDL_Surface *surface = SDL_CreateSurface(
		bullet.srcrect.w, bullet.srcrect.h, RENDER_PIXEL_FORMAT);
	SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);

	SDL_SetRenderDrawColor(renderer, BULLET_COLOR.r, BULLET_COLOR.g,
			       BULLET_COLOR.b, BULLET_COLOR.a);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	bullet.texture = Camera_CreateTextureFromSurface(surface);

	SDL_DestroyRenderer(renderer);
	SDL_DestroySurface(surface);

	magazine->bulletList->object = bullet;

	return true;
}

void Bullet_ReloadMagazine(BulletMagazine *magazine)
{
	if (SDL_GetTicks() - magazine->prevReloadTime > BULLET_RELOAD_TIME_MS) {
		magazine->prevReloadTime = SDL_GetTicks();
		magazine->bulletNumber = BULLET_MAX_COUNT;
	}
}

void Bullet_UpdateList(BulletList *bulletList, Uint64 deltaTime, Map *map)
{
	for (; bulletList; bulletList = bulletList->next) {
		if (!bulletList->object.texture)
			continue;

		bulletList->object.dstrect.x +=
			SDL_cosf(bulletList->object.direction) * BULLET_SPEED *
			deltaTime / 1000.0f;
		bulletList->object.dstrect.y +=
			SDL_sinf(bulletList->object.direction) * BULLET_SPEED *
			deltaTime / 1000.0f;

		if (!Map_IsPointHit(map, bulletList->object.dstrect.x,
				    bulletList->object.dstrect.y)) {
			continue;
		}

		Bullet_Delete(&bulletList->object);

		if (bulletList->prev && bulletList->next) {
			bulletList->prev->next = bulletList->next;
			bulletList->next->prev = bulletList->prev;
		}
	}
}

void Bullet_Delete(Bullet *bullet)
{
	if (!bullet->texture)
		return;
	SDL_DestroyTexture(bullet->texture);
	bullet->texture = NULL;
}

void Bullet_DeleteList(BulletList *bulletList)
{
	for (; bulletList; bulletList = bulletList->next) {
		Bullet_Delete(&bulletList->object);
	}

	free(bulletList);
}
