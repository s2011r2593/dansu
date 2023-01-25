#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <crtdbg.h>
#include <stdlib.h>

#include <stdio.h>

#include <SDL.h>

#include "dansu.h"
#include "dansu-defs.h"
#include "dansu-types.h"

int main(int argc, char* argv[]) {
	DansuOS* dansu = DS_Initialize();

	DS_LoadSurfaceIntoTexture(dansu, "./assets/dsf.bmp");
	DS_LoadSurfaceIntoTexture(dansu, "./assets/dansu-logo.bmp");

	SDL_RenderClear(dansu->renderer);
	DS_RenderTexture(dansu, 1, (GRID_WIDTH / 2) - 16, (GRID_HEIGHT / 2) - 21, 32, 42);
	SDL_RenderPresent(dansu->renderer);
	//SDL_Delay(2000);

	//SDL_RenderClear(dansu->renderer);
	//DS_PrintChar(dansu, 'f', 70, 70);
	//DS_PrintString(dansu, "loading...", 7, 13);
	//SDL_RenderPresent(dansu->renderer);


	uint8_t should_quit = 0;
	SDL_Event sdle;
	SDL_StartTextInput();
	while (should_quit == 0 && SDL_WaitEvent(&sdle)) {
		if (sdle.type == SDL_QUIT) break;

		switch (dansu->state) {
		case dsBooting:
			dansu->state = dsAcceptingUserInput;
			break;
		case dsExecuting:
			break;
		case dsAcceptingUserInput:
			DS_CheckKeyInput(dansu, sdle);
			break;
		default:
			break;
		}
	}

	DS_Exit(dansu);

	_CrtDumpMemoryLeaks();
	return 0;
}
