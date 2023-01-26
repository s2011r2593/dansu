#pragma once

#include <stdint.h>
#include <stdio.h>
#include <SDL.h>

typedef struct Console {
	char* stream;
	size_t eos;
	size_t cursor_index;
	size_t top_index;
	uint8_t screen_coords[2];
} Console;

typedef struct DansuOS {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface** surfaces;
	SDL_Texture** textures;
	Console* console;
	uint8_t max_imgs;
	uint8_t num_imgs;
	uint8_t state;
} DansuOS;
