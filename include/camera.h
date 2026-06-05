#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include <common.h>

typedef enum {
	RENDER_HEIGHT_FLOOR,
	RENDER_HEIGHT_AIR,
	RENDER_HEIGHT_UI,
} RENDER_HEIGHT;

/**
 * A camera to render object
 */
typedef struct {
	SDL_Renderer *renderer;
	SDL_FPoint pos;
} Camera;

/**
 * The object can be rendered on the screen
 */
typedef struct {
	SDL_FRect rect;
	SDL_FlipMode flipMode;
	SDL_Texture *texture;
	float direction;
	RENDER_HEIGHT height;
} Render_Object;

/**
 * The node of objects
 */
typedef struct Render_ObjectNode {
	Render_Object object;
	struct Render_ObjectNode *prev;
	struct Render_ObjectNode *next;
} Render_ObjectNode;

/**
 * Bind the renderer used to render
 */
void Camera_BindRenderer(SDL_Renderer *renderer);

/**
 * Render something on the screen
 */
void Camera_RenderObject(Render_Object *object, int row);

/**
 * Create a texture from surface
 */
SDL_Texture *Camera_CreateTextureFromSurface(SDL_Surface *surface);

/** 
 * Render a series of objects 
 */
void Camera_RenderObjects(Render_ObjectNode *objectNode, int row);

/**
 * Update camera's pos
 */
void Camera_Update(Render_Object *object, SDL_FRect *boundary);

/**
 * Get the position of object on the screen
 *
 * \returns the position of object on the screen
 */
SDL_FPoint Camera_GetPosOnScreen(SDL_FPoint *point);

/**
 * Get if object is on the screen
 *
 * \returns true if object is on the screen or false
 */
bool Camera_IsPosOnScreen(SDL_FPoint *point);

/**
 * Get the position of point on the map
 *
 * \returns the position of point on the map
 */
SDL_FPoint Camera_GetPosOnMap(SDL_FPoint *point);

/**
 * Set renderer draw color using SDL_Color
 */
inline bool Camera_SetRenderDrawColor(SDL_Renderer *renderer, SDL_Color *color)
{
	return SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b,
				      color->a);
}

#endif /* INCLUDE_CAMERA_H */