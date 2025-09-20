#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include <common.h>

/**
 * The shape of render object
 * 
 * \sa Render_Object
 */
typedef enum {
    RENDER_SHAPE_RECTANGLE,     // Rectangle
    RENDER_SHAPE_CIRCLE         // Circle
} Render_Shape;

/**
 * The object can be rendered on the screen
 */
typedef struct {
    float pos[2];           // The position of render object
    float size;             // The size of render object
    SDL_Color color;        // The color of render object
    Render_Shape shape;     // The shape of render object
} Render_Object;

/**
 * Bind the renderer used to render
 * 
 * \param renderer the renderer context
 * 
 * \sa SDL_Renderer
 */
void Camera_BindRenderer(SDL_Renderer *renderer);

/**
 * Render something on the screen
 * 
 * \param object the thing will be rendered
 * 
 * \sa Render_Object
 */
void Camera_RenderObject(Render_Object *object);

#endif /* INCLUDE_CAMERA_H */