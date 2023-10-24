#include "main.h"

int main(int argc, char *argv[]) {
    static CHIP8 emulator = {0};

    chip8_load_fonts(&emulator);

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    const uint16_t WINDOW_HEIGHT = 512;
    const uint16_t WINDOW_WIDTH = 1024;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}