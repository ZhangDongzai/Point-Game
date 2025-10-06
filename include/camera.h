#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include <common.h>

/**
 * The shape of render object
 * 
 * \sa Render_Object
 */
typedef enum {
    RENDER_SHAPE_RECT,
    RENDER_SHAPE_CIRCLE
} Render_Shape;

/**
 * A camera to render object
 */
typedef struct {
    SDL_Renderer *renderer;
    float pos[2];
} Camera;

/**
 * The object can be rendered on the screen
 */
typedef struct {
    SDL_FRect rect;
    SDL_Color color;
    Render_Shape shape;
    float direction;
} Render_Object;

/**
 * The node of objects
 */
typedef struct Render_ObjectNode
{
    Render_Object *object;
    struct Render_ObjectNode *prev;
    struct Render_ObjectNode *next;
} Render_ObjectNode;

/**
 * The boundary of a object
 */
typedef struct
{
    float up;
    float down;
    float left;
    float right;
} Render_Boundary;

/**
 * Bind the renderer used to render and set the position
 * 
 * \param renderer the renderer context
 * \param pos the position of camera
 * 
 * \sa SDL_Renderer
 */
void Camera_BindRenderer(SDL_Renderer *renderer, float *pos);

/**
 * Render something on the screen
 * 
 * \param object the thing will be rendered
 * 
 * \sa Render_Object
 */
void Camera_RenderObject(Render_Object *object);

/** Render a series of objects 
 * 
 * \param objectNode the node of objects
 * 
 * \sa Render_ObjectNode
*/
void Camera_RenderObjects(Render_ObjectNode *objectNode);

/**
 * Update camera's pos
 * 
 * \param object the object which will be render in the center
 * 
 * \sa Render_Object
 */
void Camera_Update(Render_Object *object, Render_Boundary *boundary);

#endif /* INCLUDE_CAMERA_H */