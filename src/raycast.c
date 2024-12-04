#include <raycast.h>


void renderRaycast(SDL_Renderer *renderer, Player *player, Map map) {
    float rayAngle = player->direction - (RAY_FOV / 2) + 1e-6;
    int xMap = player->x / MAP_WIDTH * MAP_WIDTH;
    int yMap = player->y / MAP_HEIGHT * MAP_HEIGHT;
    float rayAngleCos, rayAngleSin;
    float xVert, yVert, xHor, yHor, dx, dy, depthVert, depthHor, deltaDepth, depth;

    for (int ray = 0; ray < RAY_NUMBER; ray++) {
        rayAngleCos = cosf(rayAngle);
        rayAngleSin = sinf(rayAngle);

        // Horizontals
        if (rayAngleSin > 0) {
            yHor = yMap + MAP_HEIGHT;
            dy = MAP_HEIGHT;
        } else {
            yHor = yMap - 1;
            dy = -MAP_HEIGHT;
        }

        deltaDepth = dy / rayAngleSin;
        depthHor = (yHor - (float) player->y) / rayAngleSin;
        dx = depthHor * rayAngleCos;
        xHor = (float) player->x + dx;

        for (int i = 0; i < RAY_MAX_DEPTH; i++) {
            if (isHitMap(map, (int) xHor, (int) yHor)) break;
            xHor += dx; yHor += dy; depthHor += deltaDepth;
        }

        // Verticals
        if (rayAngleCos > 0) {
            xVert = xMap + MAP_WIDTH;
            dx = MAP_WIDTH;
        } else {
            xVert = xMap - 1;
            dx = -MAP_WIDTH;
        }

        deltaDepth = dx / rayAngleCos;
        depthVert = (xVert - (float) player->x) / rayAngleCos;
        dy = depthVert * rayAngleSin;
        yVert = (float) player->y + dy;

        for (int i = 0; i < RAY_MAX_DEPTH; i++) {
            if (isHitMap(map, (int) xVert, (int) yVert)) break;
            xVert += dx; yVert += dy; depthVert += deltaDepth;
        }

        depth = (depthVert < depthHor) ? depthVert : depthHor;

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawLine(renderer, player->x, player->y,
            player->x + (int)(depth * rayAngleCos),
            player->y + (int)(depth * rayAngleSin));

        rayAngle += RAY_DELTA_ANGLE;
    }
}
