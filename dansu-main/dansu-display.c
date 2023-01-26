#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL.h>

#include "dansu-display.h"
#include "dansu-defs.h"

void DS_LoadSurfaceIntoTexture(DansuOS* dansu, const char* path) {
	dansu->surfaces[dansu->num_imgs] = SDL_LoadBMP(path);
	if (dansu->surfaces[dansu->num_imgs] == 0) {
		printf("Failed to load bmp: %s\n", SDL_GetError());
		exit(1);
	}

	dansu->textures[dansu->num_imgs] = SDL_CreateTextureFromSurface(dansu->renderer, dansu->surfaces[dansu->num_imgs]);
	if (dansu->textures[dansu->num_imgs] == 0) {
		printf("Failed to convert surface into texture: %s\n", SDL_GetError());
		exit(1);
	}

	dansu->num_imgs++;
}

void DS_RenderTexture(DansuOS* dansu, uint8_t index, uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
	SDL_Rect src_rect = {0, 0, w, h};
	SDL_Rect dst_rect = {x * SCREEN_SCALE, y * SCREEN_SCALE, w * SCREEN_SCALE, h * SCREEN_SCALE};
	SDL_RenderCopy(dansu->renderer, dansu->textures[index], &src_rect, &dst_rect);
}

void DS_CheckKeyInput(DansuOS* dansu, SDL_Event e) {
	uint32_t k;
	switch (e.type) {
	case SDL_TEXTINPUT:
		printf("%c", e.text.text[0]);
		break;
	case SDL_KEYDOWN:
		k = e.key.keysym.sym;
		switch (k) {
		case 0x08:
			printf(" BACKSPACE ");
			break;
		case 0x0d:
			printf("\n");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
