#include <enemy.h>

Enemys Enemy_Init(SDL_Renderer *renderer)
{
	Enemys enemys;

	enemys.texture = SDL_CreateTexture(renderer, RENDER_PIXEL_FORMAT,
					   SDL_TEXTUREACCESS_TARGET, 1, 1);
	SDL_SetRenderTarget(renderer, enemys.texture);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);

	enemys.list = calloc(1, sizeof(struct list_head));
	INIT_LIST_HEAD(enemys.list);

	return enemys;
}

void Enemy_Create(Enemys *enemys, const SDL_FPoint *pos)
{
	Enemy *enemy = calloc(1, sizeof(Enemy));

	enemy->direction = 0.0f;
	enemy->flipMode = SDL_FLIP_NONE;
	enemy->height = RENDER_HEIGHT_FLOOR;
	enemy->rect = (SDL_FRect){ pos->x, pos->y, 1, 1 };
	enemy->texture = enemys->texture;

	list_add(&enemy->list, enemys->list);
}

bool Enemy_IsHit(Enemys *enemys, const SDL_FPoint *pos)
{
	Enemy *enemy, *temp;
	list_for_each_entry_safe(enemy, temp, enemys->list, list) {
		if (SDL_PointInRectFloat(pos, &enemy->rect)) {
			list_del(&enemy->list);
			free(enemy);
			return true;
		}
	}
	return false;
}

void Enemy_Delete(Enemys *enemys)
{
	Enemy *enemy, *temp;
	list_for_each_entry_safe(enemy, temp, enemys->list, list) {
		list_del(&enemy->list);
		free(enemy);
	}
	SDL_DestroyTexture(enemys->texture);
}
