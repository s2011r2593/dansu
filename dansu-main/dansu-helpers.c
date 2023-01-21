#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "dansu-helpers.h"

void CheckAlloc(void* ptr, const char* msg) {
	if (ptr == NULL) {
		printf("%s\n", msg);
		exit(-1);
	}
}

// Taken from http://www.cse.yorku.ca/~oz/hash.html
uint64_t SimpleHash(char* str) {
	uint8_t* casted = (uint8_t*) str;

	uint64_t hash = 5381;
	int c;
	while (c = *casted++) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}
