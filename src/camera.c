#include <camera.h>

static Camera camera;

void Camera_BindRenderer(SDL_Renderer *renderer)
{
	camera.renderer = renderer;
}

SDL_Texture *Camera_CreateTextureFromSurface(SDL_Surface *surface)
{
	SDL_Texture *texture = SDL_CreateTexture(camera.renderer,
						 RENDER_PIXEL_FORMAT,
						 SDL_TEXTUREACCESS_STREAMING,
						 surface->w, surface->h);
	SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
	return texture;
}

void Camera_RenderObject(Render_Object *object, int row)
{
	float objectRow = object->rect.y;
	switch (object->height) {
	case RENDER_HEIGHT_FLOOR:
		objectRow += object->rect.h;
		break;
	case RENDER_HEIGHT_AIR:
		objectRow += object->rect.h / 2.0f;
		break;
	case RENDER_HEIGHT_UI:
		objectRow = row;
		break;
	}
	if (!(row <= objectRow && objectRow < row + 1))
		return;

	SDL_FRect rect = { (object->rect.x - camera.pos.x) * WINDOW_SCALE +
				   WINDOW_WIDTH / 2.0f,
			   (object->rect.y - camera.pos.y) * WINDOW_SCALE +
				   WINDOW_HEIGHT / 2.0f,
			   object->rect.w * WINDOW_SCALE,
			   object->rect.h * WINDOW_SCALE };
	double angle = object->direction / SDL_PI_D * 180;
	SDL_RenderTextureRotated(camera.renderer, object->texture, NULL, &rect,
				 angle, NULL, object->flipMode);
}

void Camera_RenderObjects(Render_ObjectNode *node, int row)
{
	for (; node; node = node->next) {
		if (!node->object.texture)
			continue;
		Camera_RenderObject(&node->object, row);
	}
}

void Camera_Update(Render_Object *object, SDL_FRect *boundary)
{
	camera.pos.x = object->rect.x;
	camera.pos.y = object->rect.y;

	float left = WINDOW_WIDTH_SCALE / 2.0f + boundary->x;
	float right = -WINDOW_WIDTH_SCALE / 2.0f + boundary->x + boundary->w;
	float up = WINDOW_HEIGHT_SCALE / 2.0f + boundary->y;
	float bottom = WINDOW_HEIGHT_SCALE / 2.0f + boundary->y + boundary->h;

	if (object->rect.x < left) {
		camera.pos.x = left;
	} else if (object->rect.x > right) {
		camera.pos.x = right;
	}
	if (object->rect.y < up) {
		camera.pos.y = up;
	} else if (object->rect.y > bottom) {
		camera.pos.y = bottom;
	}
}

SDL_FPoint Camera_GetPosOnScreen(SDL_FPoint *point)
{
	return (SDL_FPoint){
		(point->x - camera.pos.x) * WINDOW_SCALE + WINDOW_WIDTH / 2.0f,
		(point->y - camera.pos.y) * WINDOW_SCALE + WINDOW_HEIGHT / 2.0f
	};
}

bool Camera_IsPosOnScreen(SDL_FPoint *point)
{
	SDL_FPoint pos = Camera_GetPosOnScreen(point);
	return !(pos.x < 0 || pos.x >= WINDOW_WIDTH || pos.y < 0 ||
		 pos.y >= WINDOW_HEIGHT);
}

SDL_FPoint Camera_GetPosOnMap(SDL_FPoint *point)
{
	return (SDL_FPoint){
		(point->x - WINDOW_WIDTH / 2.0f) / WINDOW_SCALE + camera.pos.x,
		(point->y - WINDOW_HEIGHT / 2.0f) / WINDOW_SCALE + camera.pos.y
	};
}

extern inline bool Camera_SetRenderDrawColor(SDL_Renderer *renderer,
					     SDL_Color *color);

extern inline void Camera_GetRectCenterFloat(const SDL_FRect *rect,
					     SDL_FPoint *point);