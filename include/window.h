#ifndef INCLUDE_WINDOW_H
#define INCLUDE_WINDOW_H

#include <bullet.h>
#include <enemy.h>
#include <player.h>
#include <map.h>
#include <ui.h>
#include <camera.h>
#include <common.h>

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font *font;
	UI ui;

	Player *player;
	Enemys enemys;
	struct list_head *bulletList;
	Map map;

	bool isMouseUsable;
	Uint64 preFrameTime;
	Uint64 deltaTime;
} App;

#endif /* INCLUDE_WINDOW_H */
