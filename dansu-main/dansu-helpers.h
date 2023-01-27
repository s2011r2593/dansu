#pragma once
#include <stdint.h>

void* Mallocate(size_t size, const char* msg);
void* Callocate(size_t count, size_t dat_size, const char* msg);

uint64_t SimpleHash(char* str_ptr);
