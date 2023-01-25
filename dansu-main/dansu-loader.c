#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "dansu-loader.h"
#include "dansu-helpers.h"
#include "dansu-defs.h"

const int GRID_WIDTH = 160;
const int GRID_HEIGHT = 120;
const int SCREEN_SCALE = 6;

const uint64_t HASHED_PASS = 0xfa10ce17f79cf390;

void InitializeSDL(DansuOS* dansu) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	uint32_t window_flags = 0;
	SDL_Window* window = SDL_CreateWindow(
		"d a n s u",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		GRID_WIDTH * SCREEN_SCALE, GRID_HEIGHT * SCREEN_SCALE,
		window_flags
	);
	if (window == 0) {
		printf("Failed to initialize SDL window: %s\n", SDL_GetError());
		exit(1);
	}

	uint32_t renderer_flags = SDL_RENDERER_SOFTWARE;
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (renderer == 0) {
		printf("Failed to initialize SDL renderer: %s\n", SDL_GetError());
		exit(1);
	}

	dansu->window = window;
	dansu->renderer = renderer;
}

void DeinitializeSDL(DansuOS* dansu) {
	for (uint8_t i = 0; i < dansu->num_imgs; i++) {
		SDL_DestroyTexture(dansu->textures[i]);
		SDL_FreeSurface(dansu->surfaces[i]);
	}

	SDL_DestroyWindow(dansu->window);

	SDL_Quit();
}

DansuOS* DS_Initialize() {
	DansuOS* dansu = (DansuOS*) malloc(sizeof(DansuOS));
	CheckAlloc(dansu, "Failed to allocate dansu");
	dansu->max_imgs = 16;
	dansu->num_imgs = 0;
	dansu->state = dsBooting;
	dansu->cursor[0] = 0;
	dansu->cursor[1] = 0;

	dansu->surfaces = (SDL_Surface**) malloc(dansu->max_imgs * sizeof(SDL_Surface*));
	CheckAlloc(dansu->surfaces, "Failed to allocate surfaces");
	dansu->textures = (SDL_Texture**) malloc(dansu->max_imgs * sizeof(SDL_Texture*));
	CheckAlloc(dansu->textures, "Failed to allocate textures");

	InitializeSDL(dansu);

	return dansu;
}

void DS_Exit(DansuOS* dansu) {
	DeinitializeSDL(dansu);

	free(dansu->textures);
	free(dansu->surfaces);
	free(dansu);
}
