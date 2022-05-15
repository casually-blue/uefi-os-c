#pragma once
#include<stdint.h>

void* malloc(uint64_t allocation_size);
void free(void* location);
void* realloc(void* location, uint64_t new_size);
