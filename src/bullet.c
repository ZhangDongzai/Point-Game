#include <bullet.h>

struct list_head *Bullet_Init()
{
	struct list_head *list = calloc(1, sizeof(struct list_head));
	INIT_LIST_HEAD(list);
	return list;
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

	Bullet *bullet = (Bullet *)calloc(1, sizeof(Bullet));
	bullet->rect.x = pos->x - BULLET_WIDTH / 2.0f;
	bullet->rect.y = pos->y - BULLET_HEIGHT / 2.0f;
	bullet->rect.w = BULLET_WIDTH;
	bullet->rect.h = BULLET_HEIGHT;
	bullet->flipMode = SDL_FLIP_NONE;
	bullet->direction = direction;
	bullet->height = RENDER_HEIGHT_AIR;
	bullet->texture = magazine->texture;

	list_add(&bullet->list, magazine->bulletList);

	return true;
}

void Bullet_ReloadMagazine(BulletMagazine *magazine)
{
	if (SDL_GetTicks() - magazine->prevReloadTime > BULLET_RELOAD_TIME_MS) {
		magazine->prevReloadTime = SDL_GetTicks();
		magazine->bulletNumber = BULLET_MAX_COUNT;
	}
}

void Bullet_UpdateList(struct list_head *bulletList, Uint64 deltaTime, Map *map,
		       Enemys *enemys)
{
	float speed = BULLET_SPEED * deltaTime / 1000.0f;
	SDL_FPoint pos;
	Bullet *node, *temp;
	list_for_each_entry_safe(node, temp, bulletList, list) {
		node->rect.x += SDL_cosf(node->direction) * speed;
		node->rect.y += SDL_sinf(node->direction) * speed;

		Camera_GetRectCenterFloat(&node->rect, &pos);

		if (Map_IsPointHit(map, node->rect.x,
				   node->rect.y) ||
		    Enemy_IsHit(enemys, &pos)) {
			list_del(&node->list);
			free(node);
		}
	}
}

void Bullet_DeleteList(struct list_head *bulletList)
{
	Bullet *temp, *node;
	list_for_each_entry_safe(node, temp, bulletList, list) {
		list_del(&node->list);
		free(node);
	}
}
