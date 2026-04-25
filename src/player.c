#include <player.h>

Player *Player_Create(BulletList *bulletList)
{
	Player *player = (Player *)calloc(1, sizeof(Player));
	player->magazine.bulletList = bulletList;
	player->magazine.bulletNumber = BULLET_MAX_COUNT;
	player->object = (Render_Object *)calloc(1, sizeof(Render_Object));
	player->object->rect.x = PLAYER_DEFAULT_POS[0];
	player->object->rect.y = PLAYER_DEFAULT_POS[1];
	player->object->rect.w = player->object->rect.h = PLAYER_SIZE;
	player->object->direction = PLAYER_DEFAULT_DIRECTION;
	player->object->texture =
		Painter_DrawCircle(PLAYER_SIZE / 2.0f, PLAYER_COLOR, true);

	return player;
}

void Player_Update(Player *player, Uint64 deltaTime, BulletList *bulletList)
{
	const bool *keyboardState = SDL_GetKeyboardState(NULL);
	float sin = PLAYER_MOVE_SPEED * deltaTime / 1000.0f *
		    SDL_sinf(player->object->direction);
	float cos = PLAYER_MOVE_SPEED * deltaTime / 1000.0f *
		    SDL_cosf(player->object->direction);
	float turn = PLAYER_TURN_SPEED * deltaTime / 1000.0f;
	float x = 0, y = 0;
	if (keyboardState[SDL_SCANCODE_W]) {
		x = cos;
		y = sin;
	}
	if (keyboardState[SDL_SCANCODE_S]) {
		x = -cos;
		y = -sin;
	}

	player->object->rect.x += x;
	if (Map_IsHit(player->object->rect.x, player->object->rect.y) ||
	    Map_IsHit(player->object->rect.x + player->object->rect.w,
		      player->object->rect.y + player->object->rect.h)) {
		player->object->rect.x -= x;
	}

	player->object->rect.y += y;
	if (Map_IsHit(player->object->rect.x, player->object->rect.y) ||
	    Map_IsHit(player->object->rect.x + player->object->rect.w,
		      player->object->rect.y + player->object->rect.h)) {
		player->object->rect.y -= y;
	}

	if (keyboardState[SDL_SCANCODE_A]) {
		player->object->direction -= turn;
	}
	if (keyboardState[SDL_SCANCODE_D]) {
		player->object->direction += turn;
	}

	if (keyboardState[SDL_SCANCODE_J]) {
		Bullet_Create(&player->magazine, player->object);
	} else if (keyboardState[SDL_SCANCODE_R]) {
		Bullet_ReloadMagazine(&player->magazine);
	}
}

void Player_Delete(Player *player)
{
	SDL_DestroyTexture(player->object->texture);
	free(player->object);
	free(player);
}
