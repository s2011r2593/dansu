#pragma once

#include <stdint.h>
#include <stdio.h>
#include <SDL.h>

typedef struct DansuOS {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface** surfaces;
	SDL_Texture** textures;
	uint8_t max_imgs;
	uint8_t num_imgs;
	uint8_t state;
	uint8_t cursor[2];
} DansuOS;

