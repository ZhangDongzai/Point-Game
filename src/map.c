#include <map.h>

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

Render_ObjectNode *Map_GetObjects() {
    Render_ObjectNode *firstNode = NULL;
    Render_ObjectNode *lastNode = firstNode;

    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int column = 0; column < MAP_WIDTH; column++) {
            if (map[row][column] == 0) continue;

            Render_ObjectNode *node = (Render_ObjectNode *)malloc(sizeof(Render_ObjectNode));
            Render_Object *object = (Render_Object *)malloc(sizeof(Render_Object));
            
            object->color = MAP_COLOR;
            object->direction = 0.0f;
            object->rect.x = column + 0.5f;
            object->rect.y = row + 0.5f;
            object->shape = RENDER_SHAPE_RECT;
            object->rect.w = object->rect.h = 1.0f;

            if (lastNode != NULL) {
                lastNode->next = node;
            } else {
                firstNode = node;
            }

            node->object = object;
            lastNode = node;
        }
    }
    lastNode->next = NULL;

    return firstNode;
}

Render_Boundary* Map_GetBoundary() {
    Render_Boundary *boundary = (Render_Boundary *)malloc(sizeof(Render_Boundary));
    boundary->left = boundary->up = 0;
    boundary->right = MAP_WIDTH;
    boundary->down = MAP_HEIGHT;
    return boundary;
}

bool Map_IsHit(float x, float y) {
    if (map[(int)y][(int)x] == 1) {
        return true;
    }
    return false;
}

void Map_Delete(Render_ObjectNode *objectNode) {
    for (Render_ObjectNode *node = objectNode; node != NULL; node = node->next) {
        free(node->object);
    }
}
