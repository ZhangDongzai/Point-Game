#include <main.h>

App app;


int main(int argc, char *argv[]) {
    init_app();
    init_display();

    atexit(&quit_display);
    atexit(&quit_app);

    run_game();

    return 0;
}


static void init_app() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        HANDLE_ERROR("Init SDL");
    }

    // Get a pointer to the keyboard state array
    app.keyboard_state = SDL_GetKeyboardState(NULL);
}


static void quit_app() {
    SDL_Quit();
}
