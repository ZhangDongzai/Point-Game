#include <player.h>

void Player_Create(Player *player, SDL_Renderer *renderer, struct list_head *bulletList)
{
	/* Eye sight */
	player->direction = PLAYER_DEFAULT_DIRECTION;
	player->sightTexture = SDL_CreateTexture(renderer, RENDER_PIXEL_FORMAT,
						 SDL_TEXTUREACCESS_TARGET,
						 WINDOW_WIDTH, WINDOW_HEIGHT);

	/* Magazine */
	player->magazine.bulletList = bulletList;
	player->magazine.bulletNumber = BULLET_MAX_COUNT;
	SDL_Surface *temp = SDL_CreateSurface(1, 1, RENDER_PIXEL_FORMAT);
	SDL_ClearSurface(temp, BULLET_COLOR.r, BULLET_COLOR.g, BULLET_COLOR.b,
			 BULLET_COLOR.a);
	player->magazine.texture = Camera_CreateTextureFromSurface(temp);
	SDL_DestroySurface(temp);

	/* Texture */
	player->prevChangeTextureTime = 0;
	player->textureNumber = 0;
	SDL_Surface *textureSurface = SDL_LoadPNG(PLAYER_TEXTURE_FILE);
	temp = SDL_CreateSurface(PLAYER_SIZE * WINDOW_SCALE,
				 PLAYER_SIZE * WINDOW_SCALE,
				 RENDER_PIXEL_FORMAT);
	SDL_Rect rect = PLAYER_TEXTURE_EDGE;
	for (int row = 0; row < PLAYER_TEXTURE_ROWS; row++) {
		rect.y = row * PLAYER_TEXTURE_SIZE + PLAYER_TEXTURE_EDGE.y;
		for (int column = 0; column < PLAYER_TEXTURE_COLUMNS;
		     column++) {
			rect.x = column * PLAYER_TEXTURE_SIZE +
				 PLAYER_TEXTURE_EDGE.x;
			SDL_ClearSurface(temp, 0.0f, 0.0f, 0.0f, 0.0f);
			SDL_BlitSurfaceScaled(textureSurface, &rect, temp, NULL,
					      SDL_SCALEMODE_NEAREST);
			player->textures[row][column] =
				Camera_CreateTextureFromSurface(temp);
		}
	}
	SDL_DestroySurface(temp);
	SDL_DestroySurface(textureSurface);

	/* Render object */
	Render_Object *object = calloc(1, sizeof(Render_Object));
	object->rect.x = MAP_DEFAULT_POS.x - PLAYER_SIZE_HALF;
	object->rect.y = MAP_DEFAULT_POS.y - PLAYER_SIZE_HALF;
	object->rect.w = object->rect.h = PLAYER_SIZE;
	object->direction = 0.0f;
	object->texture = player->textures[0][0];
	object->height = RENDER_HEIGHT_FLOOR;

	INIT_LIST_HEAD(&player->list);
	list_add(&object->list, &player->list);
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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	/* Draw black translucent background */
	Camera_SetRenderDrawColor(renderer, &COLOR_TRANSLUCENT_BLACK);
	SDL_RenderClear(renderer);

	/* Draw transparent sight */
	SDL_FPoint vertical, horizontal;
	float verticalDepth, horizontalDepth;
	float sin, cos;
	bool isHitWall;
	SDL_Vertex vertices[PLAYER_SIGHT_RAY_NUMBER + 1];
	SDL_FPoint endPos;
	Render_Object *object =
		list_first_entry(&player->list, Render_Object, list);
	SDL_FPoint pos = { object->rect.x + PLAYER_SIZE_HALF,
			   object->rect.y + PLAYER_SIZE_HALF };

	int columns = SDL_ceilf(WINDOW_WIDTH_SCALE);
	int rows = SDL_ceilf(WINDOW_HEIGHT_SCALE);
	bool wallState[rows][columns];
	memset(wallState, false, sizeof(bool) * rows * columns);
	SDL_FRect wallRect = { 0, 0, WINDOW_SCALE,
			       WINDOW_SCALE + MAP_WALL_DELTA };
	SDL_FPoint start = { 0, 0 };
	start = Camera_GetPosOnMap(&start);
	start.x = (int)start.x, start.y = (int)start.y;

	Camera_SetRenderDrawColor(renderer, &COLOR_ZERO);
	vertices[0].position = Camera_GetPosOnScreen(&pos);
	vertices[0].color = COLOR_ZERO_FLOAT;

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
		int row = (int)endPos.y - start.y;
		int column = (int)endPos.x - start.x;
		if (row >= 0 && row < rows && column >= 0 && column < columns)
			wallState[row][column] = true;
	}

	for (int i = 2; i < rayNumber + 1; i++) {
		vertices[1] = vertices[i - 1], vertices[2] = vertices[i];
		SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
	}

	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < columns; column++) {
			pos.x = start.x + column;
			pos.y = start.y + row;

			if (!Map_IsPointHit(map, pos.x, pos.y))
				continue;

			pos = Camera_GetPosOnScreen(&pos);
			wallRect.x = pos.x;
			wallRect.y = pos.y - MAP_WALL_DELTA;

			if (!wallState[row][column])
				Camera_SetRenderDrawColor(
					renderer, &COLOR_TRANSLUCENT_BLACK);
			else
				Camera_SetRenderDrawColor(renderer,
							  &COLOR_ZERO);
			SDL_RenderFillRect(renderer, &wallRect);
		}
	}

	Painter_DrawCircle(renderer, vertices[0].position.x,
			   vertices[0].position.y, PLAYER_SIZE * WINDOW_SCALE,
			   COLOR_ZERO, true);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawBlendMode(renderer, RENDER_BLENDMODE);
	SDL_RenderTexture(renderer, player->sightTexture, NULL, NULL);
}

void Player_Update(Player *player, Uint64 deltaTime, Map *map,
		   bool *isMouseUsable)
{
	float x = 0, y = 0, mouseX, mouseY, speed;

	SDL_MouseButtonFlags mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	SDL_FPoint playerPos;
	Render_Object *object =
		list_first_entry(&player->list, Render_Object, list);
	Camera_GetRectCenterFloat(&object->rect, &playerPos);
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

	if (!Map_IsPointHit(map, object->rect.x + x,
			    object->rect.y + object->rect.h) &&
	    !Map_IsPointHit(map, object->rect.x + object->rect.w + x,
			    object->rect.y + object->rect.h)) {
		object->rect.x += x;
	}
	if (!Map_IsPointHit(map, object->rect.x,
			    object->rect.y + object->rect.h + y) &&
	    !Map_IsPointHit(map, object->rect.x + object->rect.w,
			    object->rect.y + object->rect.h + y)) {
		object->rect.y += y;
	}

	Camera_GetRectCenterFloat(&object->rect, &playerPos);

	/* Shoot & reload */
	if ((mouseState & SDL_BUTTON_LMASK) && *isMouseUsable) {
		Bullet_Create(&player->magazine, &playerPos, player->direction);
	} else if (!(mouseState & SDL_BUTTON_LMASK) && !*isMouseUsable) {
		*isMouseUsable = true;
	} else if (keyboardState[SDL_SCANCODE_R]) {
		Bullet_ReloadMagazine(&player->magazine);
	}

	/* Change texture */
	if (player->direction > (SDL_PI_F / 4 * 3) ||
	    player->direction < -(SDL_PI_F / 4 * 3))
		object->flipMode = SDL_FLIP_HORIZONTAL;
	else
		object->flipMode = SDL_FLIP_NONE;

	Uint64 time = SDL_GetTicks();
	if (time - player->prevChangeTextureTime <
	    PLAYER_TEXTURE_CHANGE_DELTA_TIME_MS)
		return;
	player->prevChangeTextureTime = time;

	int row = x || y ? PLAYER_TEXTURE_ROW_MOVE[0] :
			   PLAYER_TEXTURE_ROW_IDLE[0];
	int column = player->textureNumber % PLAYER_TEXTURE_COLUMNS;

	if (player->direction > (SDL_PI_F / 4) &&
	    player->direction < (SDL_PI_F / 4 * 3))
		/* Nothing */;
	else if (player->direction < -(SDL_PI_F / 4) &&
		 player->direction > -(SDL_PI_F / 4 * 3))
		row += 2;
	else
		row++;

	if (column >= 0 && column < 5)
		column++;
	else
		column = 0;

	player->textureNumber = column + row * PLAYER_TEXTURE_COLUMNS;
	object->texture = player->textures[row][column];
}

void Player_Delete(Player *player)
{
	/* Texture */
	for (int row = 0; row < PLAYER_TEXTURE_ROWS; row++) {
		for (int column = 0; column < PLAYER_TEXTURE_COLUMNS;
		     column++) {
			SDL_DestroyTexture(player->textures[row][column]);
		}
	}

	/* Eye sight */
	SDL_DestroyTexture(player->sightTexture);

	free(list_first_entry(&player->list, Render_Object, list));
}
