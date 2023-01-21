#pragma once

#include <stdint.h>
#include <stdio.h>
#include <SDL.h>

#define MAX_USERNAME_LENGTH 16

struct User {
	char username[MAX_USERNAME_LENGTH];	// TODO: maybe consider moving into defines/consts or something
	uint64_t password;
	char pfp;
};

typedef union UserBytes {
	uint8_t b[sizeof(struct User)];
	struct User u;
} UserBytes;

typedef struct DansuOS {
	SDL_Window* window;
	SDL_Renderer* renderer;
	FILE* user_db_f;
	uint64_t num_users;
	UserBytes* users;
	uint8_t authenticated;
} DansuOS;
