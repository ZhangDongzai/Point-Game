#ifndef INCLUDE_WINDOW_H
#define INCLUDE_WINDOW_H

#include <bullet.h>
#include <player.h>
#include <infoLabel.h>
#include <map.h>
#include <camera.h>
#include <common.h>

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font *font;

	Player player;
	InfoLabel infoLabel;
	BulletList *bulletList;
	Map map;

	Uint64 preFrameTime;
	Uint64 deltaTime;
} App;

#endif /* INCLUDE_WINDOW_H */
