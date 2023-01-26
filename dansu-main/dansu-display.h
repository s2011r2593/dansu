#pragma once

#include <SDL.h>

#include "dansu-types.h"

void DS_LoadSurfaceIntoTexture(DansuOS* dansu, const char* path);
void DS_RenderTexture(DansuOS* dansu, uint8_t index, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void DS_CheckKeyInput(DansuOS* dansu, SDL_Event e);
