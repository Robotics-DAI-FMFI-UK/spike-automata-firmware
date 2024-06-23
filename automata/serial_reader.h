#pragma once

#include <inttypes.h>

// returns 1 if line was read or 0 if timeout
uint8_t read_line(uint8_t **destination_pointer);