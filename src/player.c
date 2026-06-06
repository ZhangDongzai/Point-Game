#include <SDL3/SDL_render.h>
#include <player.h>

Player Player_Create(SDL_Renderer *renderer, BulletList *bulletList)
{
	Player player;

	/* Eye sight */
	player.direction = PLAYER_DEFAULT_DIRECTION;
	player.sightTexture = SDL_CreateTexture(renderer, RENDER_PIXEL_FORMAT,
						SDL_TEXTUREACCESS_TARGET,
						WINDOW_WIDTH, WINDOW_HEIGHT);

	/* Magazine */
	player.magazine.bulletList = bulletList;
	player.magazine.bulletNumber = BULLET_MAX_COUNT;
	SDL_Surface *temp = SDL_CreateSurface(1, 1, RENDER_PIXEL_FORMAT);
	SDL_ClearSurface(temp, BULLET_COLOR.r, BULLET_COLOR.g, BULLET_COLOR.b,
			 BULLET_COLOR.a);
	player.magazine.bullet = Camera_CreateTextureFromSurface(temp);
	SDL_DestroySurface(temp);

	/* Texture */
	player.prevChangeTextureTime = SDL_GetTicks();
	player.textureNumber = 4;
	SDL_Surface *textureSurface = SDL_LoadPNG(PLAYER_TEXTURE_FILE);
	temp = SDL_CreateSurface(PLAYER_SIZE * WINDOW_SCALE,
				 PLAYER_SIZE * WINDOW_SCALE,
				 RENDER_PIXEL_FORMAT);
	SDL_Rect rect = { 0, 0, PLAYER_TEXTURE_SIZE, PLAYER_TEXTURE_SIZE };
	for (int i = 0; i < PLAYER_TEXTURE_NUMBER; i++) {
		rect.x = i * PLAYER_TEXTURE_SIZE;
		SDL_BlitSurfaceScaled(textureSurface, &rect, temp, NULL,
				      SDL_SCALEMODE_NEAREST);
		player.textures[i] = Camera_CreateTextureFromSurface(temp);
		SDL_ClearSurface(temp, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	SDL_DestroySurface(temp);
	SDL_DestroySurface(textureSurface);

	/* Render object */
	player.object.rect.x = MAP_DEFAULT_POS.x - PLAYER_SIZE_HALF;
	player.object.rect.y = MAP_DEFAULT_POS.y - PLAYER_SIZE_HALF;
	player.object.rect.w = player.object.rect.h = PLAYER_SIZE;
	player.object.direction = 0.0f;
	player.object.texture = player.textures[0];
	player.object.height = RENDER_HEIGHT_FLOOR;

	return player;
}

/**
 * Calculate ray
 *
 * \returns true if the ray hits the wall, otherwise false
 */
static inline bool _Calculate_Ray(const float *sin, const float *cos,
				  float *depth, Map *map, bool isVertical,
				  const SDL_FPoint *start, SDL_FPoint *end)
{
	float deltaX, deltaY, deltaDepth;

	if (isVertical) {
		deltaX = *cos < 0 ? -1.0f : 1.0f;
		end->x = *cos < 0 ? (int)start->x - 0.001f : (int)start->x + 1;
		*depth = (end->x - start->x) / *cos;
		end->y = start->y + *depth * *sin;
		deltaDepth = deltaX / *cos;
		deltaY = deltaDepth * *sin;
	} else {
		deltaY = *sin < 0 ? -1.0f : +1.0f;
		end->y = *sin < 0 ? (int)start->y - 0.001f : (int)start->y + 1;
		*depth = (end->y - start->y) / *sin;
		end->x = start->x + *depth * *cos;
		deltaDepth = deltaY / *sin;
		deltaX = deltaDepth * *cos;
	}

	for (int i = 0; i < MAP_MAX_LENGTH; i++) {
		if (!Camera_IsPosOnScreen(end))
			break;
		if (Map_IsPointHit(map, end->x, end->y))
			return true;
		end->x += deltaX;
		end->y += deltaY;
		*depth += deltaDepth;
	}
	return false;
}

static inline void _Reduce_Vertex(SDL_Vertex *vertex, int *number)
{
	if (*number <= 2)
		return;

	if (vertex[*number - 2].position.x == vertex[*number - 1].position.x &&
	    vertex[*number - 1].position.x == vertex[*number].position.x) {
		vertex[*number - 1].position.y = vertex[*number].position.y;
		(*number)--;
		return;
	}

	if (vertex[*number - 2].position.y == vertex[*number - 1].position.y &&
	    vertex[*number - 1].position.y == vertex[*number].position.y) {
		vertex[*number - 1].position.x = vertex[*number].position.x;
		(*number)--;
		return;
	}
}

void Player_DrawSight(SDL_Renderer *renderer, Player *player, Map *map)
{
	SDL_SetRenderTarget(renderer, player->sightTexture);
	/* Draw black translucent background */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
	SDL_RenderClear(renderer);

	/* Draw transparent sight */
	SDL_FPoint vertical, horizontal;
	float verticalDepth, horizontalDepth;
	float sin, cos;
	bool isHitWall;
	SDL_Vertex vertices[PLAYER_SIGHT_RAY_NUMBER + 1];
	SDL_FPoint endPos;
	SDL_FPoint pos = { player->object.rect.x + PLAYER_SIZE_HALF,
			   player->object.rect.y + PLAYER_SIZE_HALF };
	SDL_FRect wallRect = { 0, 0, WINDOW_SCALE,
			       WINDOW_SCALE + MAP_WALL_DELTA };

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	vertices[0].position = Camera_GetPosOnScreen(&pos);
	vertices[0].color = (SDL_FColor){ 0.0f, 0.0f, 0.0f, 0.0f };

	int rayNumber = 0;
	for (float degree = player->direction - PLAYER_SIGHT_FOV_HALF;
	     degree < player->direction + PLAYER_SIGHT_FOV_HALF;
	     degree += PLAYER_SIGHT_RAY_DELTA) {
		sin = SDL_sinf(degree);
		cos = SDL_cosf(degree);

		isHitWall = _Calculate_Ray(&sin, &cos, &verticalDepth, map,
					   true, &pos, &vertical);
		isHitWall |= _Calculate_Ray(&sin, &cos, &horizontalDepth, map,
					    false, &pos, &horizontal);

		if (horizontalDepth < verticalDepth) {
			endPos.x = horizontal.x;
			endPos.y = horizontal.y;
		} else {
			endPos.x = vertical.x;
			endPos.y = vertical.y;
		}

		rayNumber++;
		vertices[rayNumber].color = vertices[rayNumber - 1].color;
		vertices[rayNumber].position = Camera_GetPosOnScreen(&endPos);

		_Reduce_Vertex(vertices, &rayNumber);

		if (!isHitWall)
			continue;
		wallRect.h = Map_IsPointHit(map, endPos.x, endPos.y + 1.0f) ?
				     WINDOW_SCALE :
				     WINDOW_SCALE + MAP_WALL_DELTA;
		endPos.x = (int)endPos.x, endPos.y = (int)endPos.y;
		endPos = Camera_GetPosOnScreen(&endPos);
		wallRect.x = endPos.x, wallRect.y = endPos.y - MAP_WALL_DELTA;
		SDL_RenderFillRect(renderer, &wallRect);
	}

	for (int i = 2; i < rayNumber + 1; i++) {
		vertices[1] = vertices[i - 1], vertices[2] = vertices[i];
		SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
	}

	Painter_DrawCircle(renderer, vertices[0].position.x,
			   vertices[0].position.y, PLAYER_SIZE * WINDOW_SCALE,
			   (SDL_Color){ 0, 0, 0, 0 }, true);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderTexture(renderer, player->sightTexture, NULL, NULL);
}

void Player_Update(Player *player, Uint64 deltaTime, BulletList *bulletList,
		   Map *map, bool *isMouseUsable)
{
	float x = 0, y = 0, mouseX, mouseY, speed;

	SDL_MouseButtonFlags mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	SDL_FPoint playerPos = { player->object.rect.x + PLAYER_SIZE_HALF,
				 player->object.rect.y + PLAYER_SIZE_HALF };
	playerPos = Camera_GetPosOnScreen(&playerPos);
	speed = PLAYER_MOVE_SPEED * deltaTime / 1000.0f;
	player->direction =
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

	if (!Map_IsPointHit(map, player->object.rect.x + x,
			    player->object.rect.y + player->object.rect.h) &&
	    !Map_IsPointHit(map,
			    player->object.rect.x + player->object.rect.w + x,
			    player->object.rect.y + player->object.rect.h)) {
		player->object.rect.x += x;
	}
	if (!Map_IsPointHit(map, player->object.rect.x,
			    player->object.rect.y + player->object.rect.h +
				    y) &&
	    !Map_IsPointHit(map, player->object.rect.x + player->object.rect.w,
			    player->object.rect.y + player->object.rect.h +
				    y)) {
		player->object.rect.y += y;
	}

	/* Shoot & reload */
	if ((mouseState & SDL_BUTTON_LMASK) && *isMouseUsable) {
		Bullet_Create(&player->magazine, &player->object,
			      player->direction);
	} else if (!(mouseState & SDL_BUTTON_LMASK) && !*isMouseUsable) {
		*isMouseUsable = true;
	} else if (keyboardState[SDL_SCANCODE_R]) {
		Bullet_ReloadMagazine(&player->magazine);
	}

	/* Change texture */
	if ((player->direction > PI_HALF) || (player->direction < -PI_HALF)) {
		player->object.flipMode = SDL_FLIP_HORIZONTAL;
	} else {
		player->object.flipMode = SDL_FLIP_NONE;
	}

	Uint64 time = SDL_GetTicks();
	if (time - player->prevChangeTextureTime <
	    PLAYER_TEXTURE_CHANGE_DELTA_TIME_MS)
		return;
	player->prevChangeTextureTime = time;

	if (x || y) {
		if (player->textureNumber < 3)
			player->textureNumber++;
		else
			player->textureNumber = 0;
	} else {
		if (player->textureNumber < 4 || player->textureNumber == 7)
			player->textureNumber = 4;
		else
			player->textureNumber++;
	}

	player->object.texture = player->textures[player->textureNumber];
}

void Player_Delete(Player *player)
{
	/* Texture */
	for (int i = 0; i < PLAYER_TEXTURE_NUMBER; i++) {
		SDL_DestroyTexture(player->textures[i]);
	}

	/* Eye sight */
	SDL_DestroyTexture(player->sightTexture);
}
