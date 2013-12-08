/*****************************************************************************
 * DEBUG MEMORY                                                              *
 * See: deb_mem.h                                                            *
 *****************************************************************************/

#include <stdio.h>
#include "deb_mem.h"

static int malloced = 0; // memory that was malloced

void *dmalloc (size_t size) {
	void *ret = malloc (size);
	
	if (ret == NULL) {
		fprintf (stderr, "ERROR: Could not malloc enough memory! Terminating.\n");
		exit (EXIT_FAILURE);
	}

	malloced ++;

	return ret;
}


void dfree (void *memory) {
	free (memory);
	malloced --;
}


int get_unfreed () {
	return malloced;
}


void print_unfreed () {
	fprintf (stderr, "UNFREED: %d\n", malloced);
}