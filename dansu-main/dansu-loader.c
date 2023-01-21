#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "dansu-loader.h"
#include "dansu-helpers.h"

const int GRID_WIDTH = 160;
const int GRID_HEIGHT = 120;
const int SCREEN_SCALE = 8;
const int HEADER_LEN = 4;
const char BASE_HEADER[4] = { 0x53, 0x52, 0x00, 0x01 };


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
	SDL_DestroyWindow(dansu->window);
	SDL_Quit();
}

uint8_t ParseHeader(FILE* fptr) {
	// Magic Bytes
	if (fgetc(fptr) != 0x53 || fgetc(fptr) != 0x52) {
		return 0;
	}

	// Version Bytes
	if (fgetc(fptr) != 0x00 || fgetc(fptr) != 0x01) {
		return 0;
	}

	return 1;
}

uint8_t HandleRead(FILE* fptr, DansuOS* dansu) {
	fseek(fptr, 0, SEEK_END);
	dansu->num_users = ftell(fptr);
	rewind(fptr);

	if (dansu->num_users > HEADER_LEN && ParseHeader(fptr)) {
		dansu->num_users -= HEADER_LEN;
		dansu->num_users /= sizeof(struct User);

		dansu->users = (UserBytes*)malloc(dansu->num_users * sizeof(UserBytes));
		CheckAlloc(dansu->users, "Failed to allocate udb buffer");

		fread(&dansu->users->u, sizeof(struct User), dansu->num_users, fptr);

		fclose(fptr);

		return 1;
	}

	fclose(fptr);
	return 0;
}

void LoadUserDatabase(DansuOS* dansu) {
	// Read in user data
	FILE* udb;
	errno_t err = fopen_s(&udb, "dansu_udb", "rb");
	if (err != 0 || !HandleRead(udb, dansu)) {
		// File Doesn't Exist:
		dansu->num_users = 0;
		dansu->users = (UserBytes*)malloc(0);
		CheckAlloc(dansu->users, "Failed to allocate udb buffer");
	}

	// Reload file for writing
	err = fopen_s(&dansu->user_db_f, "dansu_udb", "wb");
	if (err != 0) {
		printf("Failed to initialize udb\n");
		exit(1);
	}
}

void CloseUserDatabase(DansuOS* dansu) {
	// Magic Bytes + Version (probably completely unnecessary)
	for (int i = 0; i < HEADER_LEN; i++) {
		fprintf(dansu->user_db_f, "%c", BASE_HEADER[i]);
	}

	// Overwrite new file data
	// Maybe should refactor at some point
	for (uint64_t i = 0; i < dansu->num_users; i++) {
		for (int j = 0; j < sizeof(UserBytes); j++) {
			fprintf(dansu->user_db_f, "%c", dansu->users[i].b[j]);
		}
	}

	fclose(dansu->user_db_f);
}

DansuOS* InitializeDansu() {
	DansuOS* dansu = (DansuOS*)malloc(sizeof(DansuOS));
	CheckAlloc(dansu, "Failed to allocate dansu");

	InitializeSDL(dansu);

	LoadUserDatabase(dansu);

	dansu->authenticated = 0;

	return dansu;
}

void ExitDansu(DansuOS* dansu) {
	DeinitializeSDL(dansu);

	CloseUserDatabase(dansu);

	free(dansu->users);

	free(dansu);
}
