#include <enemy.h>

Enemys Enemy_Init()
{
	Enemys enemys;

	SDL_Surface *surface = SDL_LoadPNG(ENEMY_TEXTURE_FILE);
	SDL_Surface *temp = SDL_CreateSurface(ENEMY_WIDTH * WINDOW_SCALE,
					      ENEMY_HEIGHT * WINDOW_SCALE,
					      RENDER_PIXEL_FORMAT);

	SDL_Rect rect = ENEMY_TEXTURE_EDGE;
	for (int row = 0; row < ENEMY_TEXTURE_ROWS; row++) {
		rect.y = row * ENEMY_TEXTURE_SIZE + ENEMY_TEXTURE_EDGE.y;
		for (int column = 0; column < ENEMY_TEXTURE_COLUMNS; column++) {
			rect.x = column * ENEMY_TEXTURE_SIZE +
				 ENEMY_TEXTURE_EDGE.x;

			SDL_ClearSurface(temp, 0.0f, 0.0f, 0.0f, 0.0f);
			SDL_BlitSurfaceScaled(surface, &rect, temp, NULL,
					      SDL_SCALEMODE_NEAREST);
			enemys.texture[row][column] =
				Camera_CreateTextureFromSurface(temp);
		}
	}

	SDL_DestroySurface(temp);
	SDL_DestroySurface(surface);

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
	enemy->rect = (SDL_FRect){ pos->x, pos->y, ENEMY_WIDTH, ENEMY_HEIGHT };
	enemy->texture = enemys->texture[0][0];

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

	for (int row = 0; row < ENEMY_TEXTURE_ROWS; row++) {
		for (int column = 0; column < ENEMY_TEXTURE_COLUMNS; column++) {
			SDL_DestroyTexture(enemys->texture[row][column]);
		}
	}
}
