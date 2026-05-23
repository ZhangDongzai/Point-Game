#include <painter.h>

void Painter_DrawCircle(SDL_Renderer *renderer, float centerX, float centerY,
			float radius, SDL_Color color, bool isSolid)
{
	float diameter = radius * 2.0f;
	float x = radius - 1.0f, y = 0.0f;
	float tx = 1.0f, ty = 1.0f;
	float error = tx - diameter;
	
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	while (x >= y) {
		if (isSolid) {
			SDL_RenderLine(renderer, centerX + x, centerY - y,
				       centerX - x, centerY + y);
			SDL_RenderLine(renderer, centerX + x, centerY + y,
				       centerX - x, centerY - y);
			SDL_RenderLine(renderer, centerX + y, centerY + x,
				       centerX - y, centerY - x);
			SDL_RenderLine(renderer, centerX + y, centerY - x,
				       centerX - y, centerY + x);
		} else {
			SDL_RenderPoint(renderer, centerX + x, centerY - y);
			SDL_RenderPoint(renderer, centerX + x, centerY + y);
			SDL_RenderPoint(renderer, centerX - x, centerY - y);
			SDL_RenderPoint(renderer, centerX - x, centerY + y);
			SDL_RenderPoint(renderer, centerX + y, centerY - x);
			SDL_RenderPoint(renderer, centerX + y, centerY + x);
			SDL_RenderPoint(renderer, centerX - y, centerY - x);
			SDL_RenderPoint(renderer, centerX - y, centerY + x);
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
}