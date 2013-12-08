/*****************************************************************************
 * LINKED LIST                                                               *
 * A limited linked list implementation where the first of the list is a     *
 * union of several structs which can only be told apart from an extra type  *
 * field.                                                                    *
 * See: list.c                                                               *
 *****************************************************************************/

#pragma once

#include "game_structs.h"

enum {LIST_SNAKE, LIST_POINT};

struct linkedlist {
	int type;
	union {
		SnakeSegment snake;
		Point point;
	};
	struct linkedlist *rest;
};

typedef struct linkedlist *LinkedList;

/**
 * Makes a LinkedList segment out of a SnakeSegment.
 */
LinkedList make_linkedlist_snake (int x, int y, int dir, LinkedList rest);

/**
 * Makes a LinkedList segment out of a point.
 */
LinkedList make_linkedlist_point (int x, int y, LinkedList rest);

/**
 * Recursively frees the memory allocated by the linked list.
 */
void free_linkedlist (LinkedList list);

/**
 * Creates a copy of "reconstruct" without the specified link "without".
 */
LinkedList list_reconstruct_without (LinkedList reconstruct, LinkedList without);