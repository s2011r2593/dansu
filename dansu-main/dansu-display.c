#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL.h>

#include "dansu-display.h"
#include "dansu-defs.h"

// 22 chars across (horiz padding of 3)
// 17 chars down   (no vertical padding)

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

void DS_PrintString(DansuOS* dansu, const char* str, uint8_t x, uint8_t y) {
	int accumulated_scaler = SCREEN_SCALE * 7;
	int max_chars_x = GRID_WIDTH / 7;
	int max_chars_y = GRID_HEIGHT / 7;
	SDL_Rect breaker = {0};
	breaker.w = 7;
	breaker.h = 7;
	breaker.x = 0x2d * 7;

	// TODO: 56 in terms of consts
	SDL_Rect src_rect = {0};
	src_rect.w = 7;
	src_rect.h = 7;

	SDL_Rect dst_rect = {0};
	dst_rect.w = 7 * SCREEN_SCALE;
	dst_rect.h = 7 * SCREEN_SCALE;
	char character;
	while (character = *str) {
		src_rect.x = character * 7;

		dst_rect.x = x * accumulated_scaler;
		dst_rect.y = y * accumulated_scaler;

		x++;
		if (x >= max_chars_x) {
			x = 0;
			y++;
			if (y >= max_chars_y) {
				return;
			}
		}

		SDL_RenderCopy(dansu->renderer, dansu->textures[0], &src_rect, &dst_rect);

		str++;
	}
}

void DS_PrintChar(DansuOS* dansu, char c, uint8_t x, uint8_t y) {
	if (x > GRID_WIDTH - 6 || y > GRID_HEIGHT - 6) return;

	SDL_Rect src_rect = {c * 7, 0, 7, 7};
	SDL_Rect dst_rect = {x * SCREEN_SCALE, y * SCREEN_SCALE, 7 * SCREEN_SCALE, 7 * SCREEN_SCALE};

	SDL_RenderCopy(dansu->renderer, dansu->textures[0], &src_rect, &dst_rect);
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
			printf(" ENTER ");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
