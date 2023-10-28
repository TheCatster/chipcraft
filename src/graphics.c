//
// Created by daniil on 10/28/23.
//

#include "../include/graphics.h"

/**
 * @brief Initialize SDL2 for the emulator
 * @param void
 * @returns void
 */
void initialize_graphics(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
}
