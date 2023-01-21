#include <stdlib.h>
#include <stdio.h>

#include "helpers.h"

void CheckAlloc(void* ptr, const char* msg) {
	if (ptr == NULL) {
		printf("%s\n", msg);
		exit(-1);
	}
}
