//
// Created by daniil on 10/28/23.
//

#include "../include/graphics.h"
#include "../include/chip8.h"

/**
 * @brief Initialize SDL2 for the emulator
 * @param screen: a pointer to an SDL_Texture pointer
 * @param renderer: a pointer to an SDL_Renderer pointer
 * @param window: a pointer to an SDL_Window pointer
 * @returns void
 */
void initialize_graphics(SDL_Texture **screen, SDL_Renderer **renderer, SDL_Window **window) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *window = SDL_CreateWindow(("chipcraft"), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                               WINDOW_HEIGHT,
                               0);
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(*renderer, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
    SDL_RenderClear(*renderer);

    *screen = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, DISPLAY_WIDTH,
                                DISPLAY_HEIGHT);
}

/**
 * @brief Deinitialize SDL2 for the emulator
 * @param screen: a pointer to an SDL_Texture pointer
 * @param renderer: a pointer to an SDL_Renderer pointer
 * @param window: a pointer to an SDL_Window pointer
 * @returns void
 */
void deinitialize_graphics(SDL_Texture *screen, SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyTexture(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * @brief Updates the texture and the current window
 * @param screen: a pointer to an SDL_Texture pointer
 * @param renderer: a pointer to an SDL_Renderer pointer
 * @param pixels: list of pixels for the texture
 * @returns void
 */
void update_graphics(SDL_Texture *screen, SDL_Renderer *renderer, uint32_t *pixels) {
    SDL_UpdateTexture(screen, NULL, pixels, DISPLAY_WIDTH * sizeof(uint32_t));

    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    position.w = DISPLAY_WIDTH;
    position.h = DISPLAY_HEIGHT;
    SDL_RenderCopy(renderer, screen, NULL, &position);
    SDL_RenderPresent(renderer);
}