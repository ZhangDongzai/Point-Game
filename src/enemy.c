#include <enemy.h>

EnemyHead Enemy_Init(SDL_Renderer *renderer)
{
	EnemyHead enemyHead;

	enemyHead.texture = SDL_CreateTexture(renderer, RENDER_PIXEL_FORMAT,
					      SDL_TEXTUREACCESS_TARGET, 1, 1);
	SDL_SetRenderTarget(renderer, enemyHead.texture);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
	enemyHead.enemy = NULL;

	return enemyHead;
}

void Enemy_Create(EnemyHead *enemys, const SDL_FPoint *pos)
{
	Enemy *temp = enemys->enemy;
	enemys->enemy = calloc(1, sizeof(Enemy));
	enemys->enemy->next = temp;

	temp = enemys->enemy;
	temp->object.direction = 0.0f;
	temp->object.flipMode = SDL_FLIP_NONE;
	temp->object.height = RENDER_HEIGHT_FLOOR;
	temp->object.rect = (SDL_FRect){ pos->x, pos->y, 1, 1 };
	temp->object.texture = enemys->texture;
}

bool Enemy_IsHit(EnemyHead *enemys, const SDL_FPoint *pos)
{
	Enemy *temp;
	for (Enemy *node = enemys->enemy; node; node = node->next) {
		if (node->next && !node->next->object.texture) {
			temp = node->next;
			node->next = temp->next;
			free(temp);
		}

		if (node->object.texture &&
		    SDL_PointInRectFloat(pos, &node->object.rect)) {
			node->object.texture = NULL;
			return true;
		}
	}
	return false;
}

void Enemy_Delete(EnemyHead *enemys)
{
	for (Enemy *node = enemys->enemy, *temp; node;) {
		temp = node;
		node = node->next;
		free(temp);
	}
	SDL_DestroyTexture(enemys->texture);
}
