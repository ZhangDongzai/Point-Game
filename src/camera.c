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

void Camera_RenderObject(Render_Object *object)
{
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

void Camera_RenderObjects(Render_ObjectNode *objectNode)
{
	for (Render_ObjectNode *node = objectNode; node != NULL;
	     node = node->next) {
		if (!node->object.texture)
			continue;
		Camera_RenderObject(&node->object);
	}
}

void Camera_Update(Render_Object *object, Render_Boundary boundary)
{
	camera.pos.x = object->rect.x;
	camera.pos.y = object->rect.y;

	boundary.left += WINDOW_WIDTH_SCALE / 2.0f;
	boundary.right -= WINDOW_WIDTH_SCALE / 2.0f;
	boundary.up += WINDOW_HEIGHT_SCALE / 2.0f - MAP_WALL_DELTA_SCALE;
	boundary.down -= WINDOW_HEIGHT_SCALE / 2.0f;

	if (object->rect.x < boundary.left) {
		camera.pos.x = boundary.left;
	} else if (object->rect.x > boundary.right) {
		camera.pos.x = boundary.right;
	}
	if (object->rect.y < boundary.up) {
		camera.pos.y = boundary.up;
	} else if (object->rect.y > boundary.down) {
		camera.pos.y = boundary.down;
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
	return !(pos.x <= 0 || pos.x >= WINDOW_WIDTH || pos.y <= 0 ||
		 pos.y >= WINDOW_HEIGHT);
}