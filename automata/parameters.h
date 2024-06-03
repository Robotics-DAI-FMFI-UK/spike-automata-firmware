#pragma once

#define MAX_NUMBER_OF_PARAMETERS 12

/**
 * Global array of pointers to pass argument to functions.
 * Index 0 is reserved for error code.
 * Indexes 1 and 2 are reserved for output variables and next for input variables.
 * Last [10, 11] indexes are reserved for message and value to print.
 */
extern void *parameters[MAX_NUMBER_OF_PARAMETERS];