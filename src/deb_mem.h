/*****************************************************************************
 * DEBUG MEMORY HEADER                                                       *
 * Provides several memory debugging tools.                                  *
 * See: deb_mem.c                                                            *
 *****************************************************************************/

#pragma once

#include <stdlib.h>

/**
 * Tries to malloc memory of the given size and makes note of the fact. If
 * malloc fails the program terminates.
 */
void *dmalloc (size_t size);

/**
 * Frees the given memory and forgets that it was ever malloced.
 */
void dfree (void *memory);

/**
 * Returns the number of times dmalloc was called minus the number of times
 * dfree was called. A value greater than 0 means you still have memory to
 * free.
 */
int get_unfreed ();


/**
 * Prints the value of get_unfreed () to stderr with some formatting.
 */
void print_unfreed ();