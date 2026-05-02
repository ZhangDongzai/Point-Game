#include <camera.h>

static Camera camera;

void Camera_BindRenderer(SDL_Renderer *renderer, float *pos)
{
	camera.renderer = renderer;
	memcpy(camera.pos, pos, sizeof(camera.pos));
}

SDL_Texture *Camera_CreateTextureFromSurface(SDL_Surface *surface)
{
	return SDL_CreateTextureFromSurface(camera.renderer, surface);
}

void Camera_RenderObject(Render_Object *object)
{
	SDL_FRect rect = { (object->rect.x - camera.pos[0]) * WINDOW_SCALE +
				   WINDOW_WIDTH / 2.0f,
			   (object->rect.y - camera.pos[1]) * WINDOW_SCALE +
				   WINDOW_HEIGHT / 2.0f,
			   object->rect.w * WINDOW_SCALE,
			   object->rect.h * WINDOW_SCALE };
	double angle = object->direction / SDL_PI_D * 180;
	SDL_RenderTextureRotated(camera.renderer, object->texture, NULL, &rect,
				 angle, NULL, SDL_FLIP_NONE);
}

void Camera_RenderObjects(Render_ObjectNode *objectNode)
{
	for (Render_ObjectNode *node = objectNode; node != NULL;
	     node = node->next) {
		if (!node->object)
			continue;
		Camera_RenderObject(node->object);
	}
}

void Camera_Update(Render_Object *object, Render_Boundary boundary)
{
	camera.pos[0] = object->rect.x;
	camera.pos[1] = object->rect.y;

	boundary.left += WINDOW_WIDTH_SCALE / 2.0f;
	boundary.right -= WINDOW_WIDTH_SCALE / 2.0f;
	boundary.up += WINDOW_HEIGHT_SCALE / 2.0f;
	boundary.down -= WINDOW_HEIGHT_SCALE / 2.0f;

	if (object->rect.x < boundary.left) {
		camera.pos[0] = boundary.left;
	} else if (object->rect.x > boundary.right) {
		camera.pos[0] = boundary.right;
	}
	if (object->rect.y < boundary.up) {
		camera.pos[1] = boundary.up;
	} else if (object->rect.y > boundary.down) {
		camera.pos[1] = boundary.down;
	}
}

SDL_FPoint Camera_GetPosOnScreen(SDL_FPoint *point)
{
	return (SDL_FPoint){
		(point->x - camera.pos[0]) * WINDOW_SCALE + WINDOW_WIDTH / 2.0f,
		(point->y - camera.pos[1]) * WINDOW_SCALE + WINDOW_HEIGHT / 2.0f
	};
}