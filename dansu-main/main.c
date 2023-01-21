#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <crtdbg.h>
#include <stdlib.h>

#include <stdio.h>

#include "dansu.h"
#include "types.h"

int main() {
	DansuOS* dansu = InitializeDansu();

	ExitDansu(dansu);

	_CrtDumpMemoryLeaks();
	return 0;
}
