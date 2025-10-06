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
            Render_ObjectNode *node = (Render_ObjectNode *)calloc(1, sizeof(Render_ObjectNode));
            Render_Object *object = (Render_Object *)calloc(1, sizeof(Render_Object));
            
            switch (map[row][column])
            {
            case MAP_CODE_WALL:
                object->color = MAP_COLOR_WALL;
                break;
            case MAP_CODE_FLOOR:
                object->color = MAP_COLOR_FLOOR;
                break;
            }
            object->direction = 0.0f;
            object->rect.x = column + 0.5f;
            object->rect.y = row + 0.5f;
            object->shape = RENDER_SHAPE_RECT;
            object->rect.w = object->rect.h = 1.0f;

            if (lastNode) {
                lastNode->next = node;
                node->prev = lastNode;
            } else {
                firstNode = node;
            }

            node->object = object;
            lastNode = node;
        }
    }
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
    if (x < 0 || y < 0 || x > MAP_WIDTH || y > MAP_HEIGHT) {
        return true;
    } else if (map[(int)y][(int)x] == 1) {
        return true;
    }
    return false;
}

void Map_Delete(Render_ObjectNode *objectNode) {
    for (Render_ObjectNode *node = objectNode; node != NULL; node = node->next) {
        free(node->object);
    }
}
