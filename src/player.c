#include <player.h>

Player Player_Create(BulletList *bulletList)
{
	Player player;

	/* Eye sight */
	player.sightSurface = SDL_CreateSurface(WINDOW_WIDTH, WINDOW_HEIGHT,
						RENDER_PIXEL_FORMAT);
	player.sightRenderer = SDL_CreateSoftwareRenderer(player.sightSurface);
	player.sightTexture =
		Camera_CreateTextureFromSurface(player.sightSurface);

	/* Magazine */
	player.magazine.bulletList = bulletList;
	player.magazine.bulletNumber = BULLET_MAX_COUNT;

	/* Render object */
	player.object.rect.x = MAP_DEFAULT_POS.x - PLAYER_SIZE_HALF;
	player.object.rect.y = MAP_DEFAULT_POS.y - PLAYER_SIZE_HALF;
	player.object.rect.w = player.object.rect.h = PLAYER_SIZE;
	player.object.direction = PLAYER_DEFAULT_DIRECTION;

	SDL_Surface *surface = SDL_CreateSurface(PLAYER_SIZE * WINDOW_SCALE,
						 PLAYER_SIZE * WINDOW_SCALE,
						 RENDER_PIXEL_FORMAT);
	SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);
	Painter_DrawCircle(renderer, PLAYER_SIZE_HALF * WINDOW_SCALE,
			   PLAYER_SIZE_HALF * WINDOW_SCALE,
			   PLAYER_SIZE_HALF * WINDOW_SCALE, PLAYER_COLOR, true);
	player.object.texture = Camera_CreateTextureFromSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroySurface(surface);

	return player;
}

void Player_DrawSight(SDL_Renderer *renderer, Player *player, Map *map)
{
	/* Draw black translucent background */
	SDL_SetRenderDrawColor(player->sightRenderer, 0, 0, 0, 128);
	SDL_RenderClear(player->sightRenderer);

	/* Draw transparent sight */
	float deltaX, deltaY;
	SDL_FPoint vertical, horizontal;
	float verticalDepth, horizontalDepth, deltaDepth;
	float sin, cos;
	int VeriticesCount = 0;
	SDL_Vertex vertices[3];
	SDL_FPoint startPos, endPos;
	SDL_FPoint pos = { player->object.rect.x + PLAYER_SIZE_HALF,
			   player->object.rect.y + PLAYER_SIZE_HALF };
	SDL_FRect wallRect = { 0, 0, WINDOW_SCALE, WINDOW_SCALE + MAP_WALL_DELTA };

	SDL_SetRenderDrawColor(player->sightRenderer, 0, 0, 0, 0);
	vertices[0].position = Camera_GetPosOnScreen(&pos);
	vertices[0].color = vertices[1].color = vertices[2].color =
		(SDL_FColor){ 0.0f, 0.0f, 0.0f, 0.0f };

	for (float degree = player->object.direction - PLAYER_SIGHT_FOV_HALF;
	     degree < player->object.direction + PLAYER_SIGHT_FOV_HALF;
	     degree += PLAYER_SIGHT_RAY_DELTA) {
		sin = SDL_sinf(degree);
		cos = SDL_cosf(degree);

		/* Vertical */
		deltaX = cos < 0 ? -1.0f : 1.0f;
		vertical.x = cos < 0 ? (int)pos.x - 0.001f : (int)pos.x + 1;
		verticalDepth = (vertical.x - pos.x) / cos;
		vertical.y = pos.y + verticalDepth * sin;
		deltaDepth = deltaX / cos;
		deltaY = deltaDepth * sin;
		for (int i = 0; i < MAP_MAX_LENGTH; i++) {
			if (!Camera_IsPosOnScreen(&vertical))
				break;
			if (Map_IsHit(map, vertical.x, vertical.y))
				break;
			vertical.x += deltaX;
			vertical.y += deltaY;
			verticalDepth += deltaDepth;
		}

		/* Horizontal */
		deltaY = sin < 0 ? -1.0f : +1.0f;
		horizontal.y = sin < 0 ? (int)pos.y - 0.001f : (int)pos.y + 1;
		horizontalDepth = (horizontal.y - pos.y) / sin;
		horizontal.x = pos.x + horizontalDepth * cos;
		deltaDepth = deltaY / sin;
		deltaX = deltaDepth * cos;
		for (int i = 0; i < MAP_MAX_LENGTH; i++) {
			if (!Camera_IsPosOnScreen(&horizontal))
				break;
			if (Map_IsHit(map, horizontal.x, horizontal.y))
				break;
			horizontal.x += deltaX;
			horizontal.y += deltaY;
			horizontalDepth += deltaDepth;
		}

		if (horizontalDepth < verticalDepth) {
			endPos.x = horizontal.x;
			endPos.y = horizontal.y;
		} else {
			endPos.x = vertical.x;
			endPos.y = vertical.y;
		}

		if (VeriticesCount < 2) {
			vertices[++VeriticesCount].position =
				Camera_GetPosOnScreen(&endPos);
			continue;
		}
		vertices[1].position = vertices[2].position;
		vertices[2].position = Camera_GetPosOnScreen(&endPos);
		SDL_RenderGeometry(player->sightRenderer, NULL, vertices, 3,
				   NULL, 0);

		endPos.x = (int)endPos.x, endPos.y = (int)endPos.y;
		endPos = Camera_GetPosOnScreen(&endPos);
		wallRect.x = endPos.x, wallRect.y = endPos.y - MAP_WALL_DELTA;
		SDL_RenderFillRect(player->sightRenderer, &wallRect);
	}
	Painter_DrawCircle(player->sightRenderer, vertices[0].position.x,
			   vertices[0].position.y, PLAYER_SIZE * WINDOW_SCALE,
			   (SDL_Color){ 0, 0, 0, 0 }, true);
	SDL_RenderPresent(player->sightRenderer);

	SDL_UpdateTexture(player->sightTexture, NULL,
			  player->sightSurface->pixels,
			  player->sightSurface->pitch);
	SDL_RenderTexture(renderer, player->sightTexture, NULL, NULL);
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

	/* Move */
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

	/* Shoot & reload */
	if (mouseState & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) {
		Bullet_Create(&player->magazine, &player->object);
	} else if (keyboardState[SDL_SCANCODE_R]) {
		Bullet_ReloadMagazine(&player->magazine);
	}
}

void Player_Delete(Player *player)
{
	SDL_DestroyTexture(player->object.texture);

	/* Eye sight */
	SDL_DestroyTexture(player->sightTexture);
	SDL_DestroyRenderer(player->sightRenderer);
	SDL_DestroySurface(player->sightSurface);
}
