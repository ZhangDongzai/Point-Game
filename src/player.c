#include <player.h>

Player *Player_Create(BulletList *bulletList)
{
	Player *player = (Player *)calloc(1, sizeof(Player));
	player->magazine.bulletList = bulletList;
	player->magazine.bulletNumber = BULLET_MAX_COUNT;
	player->object = (Render_Object *)calloc(1, sizeof(Render_Object));
	player->object->rect.x = PLAYER_DEFAULT_POS[0] - PLAYER_SIZE / 2.0f;
	player->object->rect.y = PLAYER_DEFAULT_POS[1] - PLAYER_SIZE / 2.0f;
	player->object->rect.w = player->object->rect.h = PLAYER_SIZE;
	player->object->direction = PLAYER_DEFAULT_DIRECTION;
	player->object->texture =
		Painter_DrawCircle(PLAYER_SIZE / 2.0f, PLAYER_COLOR, true);

	return player;
}

void Player_DrawSight(SDL_Renderer *renderer, Player *player)
{
	float deltaX, deltaY;
	float verticalX, verticalY, horizontalX, horizontalY;
	float verticalDepth, horizontalDepth, deltaDepth;
	float sin, cos;
	int VeriticesCount = 0;
	SDL_Vertex vertices[3];
	SDL_FPoint startPos, endPos;
	SDL_FPoint pos = { player->object->rect.x + (PLAYER_SIZE / 2.0f),
			   player->object->rect.y + (PLAYER_SIZE / 2.0f) };

	vertices[0].position = Camera_GetPosOnScreen(&pos);
	vertices[0].color = vertices[1].color = vertices[2].color =
		(SDL_FColor){ 255, 0, 0, 255 };

	for (float degree = player->object->direction - 0.5f;
	     degree < player->object->direction + 0.5f; degree += 0.01f) {
		sin = SDL_sinf(degree);
		cos = SDL_cosf(degree);

		// Vertical
		deltaX = cos < 0 ? -1.0f : 1.0f;
		verticalX = cos < 0 ? (int)pos.x - 1e-6 : (int)pos.x + 1;
		verticalDepth = (verticalX - pos.x) / cos;
		verticalY = pos.y + verticalDepth * sin;
		deltaDepth = deltaX / cos;
		deltaY = deltaDepth * sin;
		for (int i = 0; i < 20; i++) {
			if (Map_IsHit(verticalX, verticalY))
				break;
			verticalX += deltaX;
			verticalY += deltaY;
			verticalDepth += deltaDepth;
		}

		// Horizontal
		deltaY = sin < 0 ? -1.0f : +1.0f;
		horizontalY = sin < 0 ? (int)pos.y - 1e-6 : (int)pos.y + 1;
		horizontalDepth = (horizontalY - pos.y) / sin;
		horizontalX = pos.x + horizontalDepth * cos;
		deltaDepth = deltaY / sin;
		deltaX = deltaDepth * cos;
		for (int i = 0; i < 20; i++) {
			if (Map_IsHit(horizontalX, horizontalY))
				break;
			horizontalX += deltaX;
			horizontalY += deltaY;
			horizontalDepth += deltaDepth;
		}

		if (horizontalDepth < verticalDepth) {
			endPos.x = horizontalX;
			endPos.y = horizontalY;
		} else {
			endPos.x = verticalX;
			endPos.y = verticalY;
		}

		// startPos = Camera_GetPosOnScreen(&pos);
		// endPos = Camera_GetPosOnScreen(&endPos);
		// SDL_RenderLine(renderer, startPos.x, startPos.y, endPos.x,
		// 	       endPos.y);

		if (VeriticesCount < 2) {
			vertices[++VeriticesCount].position =
				Camera_GetPosOnScreen(&endPos);
			continue;
		}
		vertices[1].position = vertices[2].position;
		vertices[2].position = Camera_GetPosOnScreen(&endPos);
		SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
	}
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

	if (!Map_IsHit(player->object->rect.x + PLAYER_SIZE / 2.0f + x,
		       player->object->rect.y + PLAYER_SIZE / 2.0f)) {
		player->object->rect.x += x;
	}

	if (!Map_IsHit(player->object->rect.x + PLAYER_SIZE / 2.0f,
		      player->object->rect.y + PLAYER_SIZE / 2.0f + y)) {
		player->object->rect.y += y;
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
