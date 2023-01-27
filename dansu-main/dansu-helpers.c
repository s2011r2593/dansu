#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "dansu-helpers.h"

void* Mallocate(size_t size, const char* msg) {
	void* ptr = (void*) malloc(size);
	if (ptr == NULL) {
		printf("%s", msg);
		exit(-1);
	}

	return ptr;
}

void* Callocate(size_t count, size_t dat_size, const char* msg) {
	void* ptr = (void*) calloc(count, dat_size);
	if (ptr == NULL) {
		printf("%s", msg);
		exit(-1);
	}

	return ptr;
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
