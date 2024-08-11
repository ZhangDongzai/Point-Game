#include <display.h>


void init_display() {
    app.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (app.window == NULL) {
        HANDLE_ERROR("Create Window");
    }

    app.renderer = SDL_CreateRenderer(app.window, -1, 0);
    if (app.renderer == NULL) {
        HANDLE_ERROR("Create Renderer");
    }
}


void quit_display() {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
}


void draw_circle(SDL_Renderer *renderer, SDL_Point center, int radius, SDL_Color color) {
    int y = radius;
    int d = 3 - 2 * radius;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int x = 0; y >= x; x++) {
        SDL_RenderDrawLine(renderer, center.x + x, center.y + y, center.x - x, center.y + y);
        SDL_RenderDrawLine(renderer, center.x + y, center.y + x, center.x - y, center.y + x);
        SDL_RenderDrawLine(renderer, center.x + x, center.y - y, center.x - x, center.y - y);
        SDL_RenderDrawLine(renderer, center.x + y, center.y - x, center.x - y, center.y - x);

        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
    }
}
