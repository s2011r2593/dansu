#include <stdlib.h>

#include "dansu-console.h"
#include "dansu-helpers.h"

#include "dansu-defs.h"

const int CONSOLE_BUFFER_SIZE = 0xffff;

#define CHAR_X GRID_WIDTH / 7
#define CHAR_Y GRID_HEIGHT / 7
#define PAD_X GRID_WIDTH - (CHAR_X) * 7

const int charx = CHAR_X;
const int chary = GRID_HEIGHT / 7;
const int padx = PAD_X;

/*
	char* stream;
	size_t eos;
	size_t cursor_index;
	size_t top_index;
	uint8_t screen_coords[2];
*/

Console* Console_Initialize() {
	Console* console = (Console*) Callocate(1, sizeof(Console), "Failed to allocate console.\n");
	console->stream = (char*) Mallocate(CONSOLE_BUFFER_SIZE, "Failed to allocate console stream.\n");

	return console;
}

void Console_Destroy(Console* console) {
	free(console->stream);
	free(console);
}
