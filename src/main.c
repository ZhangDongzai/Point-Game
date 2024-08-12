#include <main.h>

App app;


int main(int argc, char *argv[]) {
    InitApp();
    InitDisplay();

    atexit(&QuitApp);
    atexit(&QuitDisplay);

    run_game();

    return 0;
}


static void InitApp() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        HANDLE_ERROR("Init SDL");
    }

    // Get a pointer to the keyboard state array
    app.keyboard_state = SDL_GetKeyboardState(NULL);
}


static void QuitApp() {
    SDL_Quit();
}
