#pragma once

#include <unistd.h>
#include <stdlib.h>
#include "print.h"

#define MEMORY_SIZE 240000

uint16_t fsa_malloc(uint32_t size);

void fsa_free();


