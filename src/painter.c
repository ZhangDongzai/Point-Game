#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_render.h>
#include <painter.h>

SDL_Texture *Painter_DrawCircle(float radius, SDL_Color color, bool isSolid)
{
	radius = radius * WINDOW_SCALE;
	float diameter = radius * 2.0f;
	float x = radius - 1.0f, y = 0.0f;
	float tx = 1.0f, ty = 1.0f;
	float error = tx - diameter;

	SDL_Surface *surface =
		SDL_CreateSurface(diameter, diameter, SDL_PIXELFORMAT_RGBA32);
	SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	while (x >= y) {
		if (isSolid) {
			SDL_RenderLine(renderer, radius + x, radius - y,
				       radius - x, radius + y);
			SDL_RenderLine(renderer, radius + x, radius + y,
				       radius - x, radius - y);
			SDL_RenderLine(renderer, radius + y, radius + x,
				       radius - y, radius - x);
			SDL_RenderLine(renderer, radius + y, radius - x,
				       radius - y, radius + x);
		} else {
			SDL_RenderPoint(renderer, radius + x, radius - y);
			SDL_RenderPoint(renderer, radius + x, radius + y);
			SDL_RenderPoint(renderer, radius - x, radius - y);
			SDL_RenderPoint(renderer, radius - x, radius + y);
			SDL_RenderPoint(renderer, radius + y, radius - x);
			SDL_RenderPoint(renderer, radius + y, radius + x);
			SDL_RenderPoint(renderer, radius - y, radius - x);
			SDL_RenderPoint(renderer, radius - y, radius + x);
		}

		if (error <= 0) {
			++y;
			error += ty;
			ty += 2;
		} else {
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}

	SDL_RenderPresent(renderer);
	SDL_Texture *texture = Camera_CreateTextureFromSurface(surface);

	SDL_DestroyRenderer(renderer);
	SDL_DestroySurface(surface);

	return texture;
}

void Painter_DrawDarkOverlay(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
	SDL_RenderFillRect(renderer, NULL);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}