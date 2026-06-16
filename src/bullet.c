#include <bullet.h>

BulletList *Bullet_CreateList()
{
	return (BulletList *)calloc(1, sizeof(BulletList));
}

bool Bullet_Create(BulletMagazine *magazine, SDL_FPoint *pos, float direction)
{
	Uint64 now = SDL_GetTicks();

	if (now - magazine->prevShootTime < BULLET_SHOOT_DELTA ||
	    now - magazine->prevReloadTime < BULLET_RELOAD_TIME_MS ||
	    magazine->bulletNumber <= 0)
		return false;

	magazine->prevShootTime = now;
	magazine->bulletNumber--;

	BulletList *node = magazine->bulletList;
	for (; node->object.texture; node = node->next)
		if (!node->next)
			node->next = Bullet_CreateList();

	Bullet *bullet = &node->object;
	bullet->rect.x = pos->x - BULLET_WIDTH / 2.0f;
	bullet->rect.y = pos->y - BULLET_HEIGHT / 2.0f;
	bullet->rect.w = BULLET_WIDTH;
	bullet->rect.h = BULLET_HEIGHT;
	bullet->flipMode = SDL_FLIP_NONE;
	bullet->direction = direction;
	bullet->height = RENDER_HEIGHT_AIR;
	bullet->texture = magazine->bullet;

	return true;
}

void Bullet_ReloadMagazine(BulletMagazine *magazine)
{
	if (SDL_GetTicks() - magazine->prevReloadTime > BULLET_RELOAD_TIME_MS) {
		magazine->prevReloadTime = SDL_GetTicks();
		magazine->bulletNumber = BULLET_MAX_COUNT;
	}
}

void Bullet_UpdateList(BulletList *node, Uint64 deltaTime, Map *map,
		       EnemyHead *enemys)
{
	float speed = BULLET_SPEED * deltaTime / 1000.0f;
	SDL_FPoint pos;
	BulletList *temp;
	for (; node; node = node->next) {
		if (node->next && !node->next->object.texture) {
			temp = node->next;
			node->next = temp->next;
			free(temp);
		}

		if (!node->object.texture)
			continue;

		node->object.rect.x += SDL_cosf(node->object.direction) * speed;
		node->object.rect.y += SDL_sinf(node->object.direction) * speed;

		Camera_GetRectCenterFloat(&node->object.rect, &pos);

		if (Map_IsPointHit(map, node->object.rect.x,
				   node->object.rect.y) ||
		    Enemy_IsHit(enemys, &pos)) {
			node->object.texture = NULL;
		}
	}
}

void Bullet_DeleteList(BulletList *bulletList)
{
	for (; bulletList; bulletList = bulletList->next)
		free(bulletList);
}
