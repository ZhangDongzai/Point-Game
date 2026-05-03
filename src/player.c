#include <player.h>

Player Player_Create(BulletList *bulletList)
{
	Player player;

	player.surface = SDL_CreateSurface(WINDOW_WIDTH, WINDOW_HEIGHT,
					   SDL_PIXELFORMAT_RGBA32);
	player.renderer = SDL_CreateSoftwareRenderer(player.surface);
	player.texture = Camera_CreateTextureFromSurface(player.surface);

	player.magazine.bulletList = bulletList;
	player.magazine.bulletNumber = BULLET_MAX_COUNT;
	player.object.rect.x = PLAYER_DEFAULT_POS[0] - PLAYER_SIZE_HALF;
	player.object.rect.y = PLAYER_DEFAULT_POS[1] - PLAYER_SIZE_HALF;
	player.object.rect.w = player.object.rect.h = PLAYER_SIZE;
	player.object.direction = PLAYER_DEFAULT_DIRECTION;
	player.object.texture = Painter_DrawCircle(
		PLAYER_SIZE_HALF * WINDOW_SCALE, PLAYER_COLOR, true);

	return player;
}

void Player_DrawSight(SDL_Renderer *renderer, Player *player, Map *map)
{
	SDL_SetRenderDrawColor(player->renderer, 0, 0, 0, 128);
	SDL_RenderClear(player->renderer);

	float deltaX, deltaY;
	float verticalX, verticalY, horizontalX, horizontalY;
	float verticalDepth, horizontalDepth, deltaDepth;
	float sin, cos;
	int VeriticesCount = 0;
	SDL_Vertex vertices[3];
	SDL_FPoint startPos, endPos;
	SDL_FPoint pos = { player->object.rect.x + PLAYER_SIZE_HALF,
			   player->object.rect.y + PLAYER_SIZE_HALF };

	vertices[0].position = Camera_GetPosOnScreen(&pos);
	vertices[0].color = vertices[1].color = vertices[2].color =
		(SDL_FColor){ 0.0f, 0.0f, 0.0f, 0.0f };

	for (float degree = player->object.direction - 0.5f;
	     degree < player->object.direction + 0.5f; degree += 0.01f) {
		sin = SDL_sinf(degree);
		cos = SDL_cosf(degree);

		// Vertical
		deltaX = cos < 0 ? -1.0f : 1.0f;
		verticalX = cos < 0 ? (int)pos.x - 1e-6 : (int)pos.x + 1;
		verticalDepth = (verticalX - pos.x) / cos;
		verticalY = pos.y + verticalDepth * sin;
		deltaDepth = deltaX / cos;
		deltaY = deltaDepth * sin;
		for (int i = 0; i < MAP_MAX_LENGTH; i++) {
			if (Map_IsHit(map, verticalX, verticalY))
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
		for (int i = 0; i < MAP_MAX_LENGTH; i++) {
			if (Map_IsHit(map, horizontalX, horizontalY))
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

		if (VeriticesCount < 2) {
			vertices[++VeriticesCount].position =
				Camera_GetPosOnScreen(&endPos);
			continue;
		}
		vertices[1].position = vertices[2].position;
		vertices[2].position = Camera_GetPosOnScreen(&endPos);
		SDL_RenderGeometry(player->renderer, NULL, vertices, 3, NULL,
				   0);
	}
	SDL_RenderPresent(player->renderer);

	SDL_UpdateTexture(player->texture, NULL, player->surface->pixels,
			  player->surface->pitch);
	SDL_RenderTexture(renderer, player->texture, NULL, NULL);
}

void Player_Update(Player *player, Uint64 deltaTime, BulletList *bulletList,
		   Map *map)
{
	float x = 0, y = 0, mouseX, mouseY, speed;

	SDL_MouseButtonFlags mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	SDL_FPoint playerPos = { player->object.rect.x + PLAYER_SIZE_HALF,
				 player->object.rect.y + PLAYER_SIZE_HALF };
	playerPos = Camera_GetPosOnScreen(&playerPos);
	speed = PLAYER_MOVE_SPEED * deltaTime / 1000.0f;
	player->object.direction =
		SDL_atan2f(mouseY - playerPos.y, mouseX - playerPos.x);
	const bool *keyboardState = SDL_GetKeyboardState(NULL);

	// Move
	if (keyboardState[SDL_SCANCODE_W])
		y -= speed;
	if (keyboardState[SDL_SCANCODE_S])
		y += speed;
	if (keyboardState[SDL_SCANCODE_A])
		x -= speed;
	if (keyboardState[SDL_SCANCODE_D])
		x += speed;

	if (x && y) {
		x *= SDL_cosf(SDL_PI_F * 0.25f);
		y *= SDL_sinf(SDL_PI_F * 0.25f);
	}

	if (!Map_IsHit(map, player->object.rect.x + PLAYER_SIZE_HALF + x,
		       player->object.rect.y + PLAYER_SIZE_HALF)) {
		player->object.rect.x += x;
	}
	if (!Map_IsHit(map, player->object.rect.x + PLAYER_SIZE_HALF,
		       player->object.rect.y + PLAYER_SIZE_HALF + y)) {
		player->object.rect.y += y;
	}

	// Shoot & reload
	if (mouseState & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) {
		Bullet_Create(&player->magazine, &player->object);
	} else if (keyboardState[SDL_SCANCODE_R]) {
		Bullet_ReloadMagazine(&player->magazine);
	}
}

void Player_Delete(Player *player)
{
	SDL_DestroyTexture(player->object.texture);
	SDL_DestroyTexture(player->texture);
	SDL_DestroyRenderer(player->renderer);
	SDL_DestroySurface(player->surface);
}
