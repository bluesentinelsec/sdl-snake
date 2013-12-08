/*****************************************************************************
 * LINKED LIST                                                               *
 * See: list.h                                                               *
 *****************************************************************************/

#include "deb_mem.h"
#include "list.h"

/******************************************************************************
	list.h FUNCTIONS
******************************************************************************/

LinkedList make_linkedlist_snake (int x, int y, int dir, LinkedList rest) {
	LinkedList ret = (LinkedList)dmalloc (sizeof (struct linkedlist));
	SnakeSegment first = {x, y, dir};
	
	ret->rest = rest;
	ret->snake = first;
	ret->type = LIST_SNAKE;

	return ret;
}


LinkedList make_linkedlist_point (int x, int y, LinkedList rest) {
	LinkedList ret = (LinkedList)dmalloc (sizeof (struct linkedlist));
	Point first = {x, y};
	
	ret->rest = rest;
	ret->point = first;
	ret->type = LIST_POINT;

	return ret;
}


void free_linkedlist (LinkedList list) {
	if (list == NULL) return;

	free_linkedlist (list->rest);
	dfree (list);
}


LinkedList list_reconstruct_without (LinkedList reconstruct, LinkedList without) {
	LinkedList iter;
	LinkedList ret = NULL;

	for (iter = reconstruct; iter != NULL; iter = iter->rest) {
		SnakeSegment to_add = iter->snake;

		if (iter == without) continue; // ignore the part we don't want
		
		ret = make_linkedlist_snake (to_add.x, to_add.y, to_add.dir, ret);
	}

	return ret;
}