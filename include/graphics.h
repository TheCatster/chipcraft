//
// Created by daniil on 10/28/23.
//

#pragma once

#include <SDL2/SDL.h>

#define WINDOW_HEIGHT 320
#define WINDOW_WIDTH 640

void initialize_graphics(SDL_Texture **screen, SDL_Renderer **renderer, SDL_Window **window);

void deinitialize_graphics(SDL_Texture *screen, SDL_Renderer *renderer, SDL_Window *window);

void update_graphics(SDL_Texture *screen, SDL_Renderer *renderer, uint32_t *pixels);