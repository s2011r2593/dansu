#pragma once
#include <stdint.h>

void CheckAlloc(void* ptr, const char* msg);
uint64_t SimpleHash(char* str_ptr);
