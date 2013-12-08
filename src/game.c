/*****************************************************************************
 * GAME STAGE                                                                *
 * A bunch of functions which defines game behavior.                         *
 * See: stage_list.h                                                         *
 *****************************************************************************/

#include "input.h" // includes boolean.h
#include "stage_list.h" // includes stage.h
#include "images.h" // includes sprite_strip.h
#include "list.h" // includes game_structs.h
#include "deb_mem.h" // includes stdlib.h
#include "sounds.h" // includes SDL_mixer.h
#include <stdio.h>

/******************************************************************************
	STATIC VARIABLES
******************************************************************************/

static int head_next_dir = DIR_EAST; // the queued direction change
static int countdown = 160; // the 321GO countdown
static int score = 0; // score

/******************************************************************************
	EXTERNAL VARIABLES
******************************************************************************/

// list of SnakeSegments with all the segments of the snake
LinkedList snake = NULL;

// pointer to the head of the snake inside the snake list
LinkedList head = NULL;
// pointer to the end of the snake inside the snake list
LinkedList end = NULL;

 // list of all turn points (actually SnakeSegments)
LinkedList turn = NULL;

// where the food is located;
Point food;

// the snake speed; should be power of 2 
int speed = 2;

/******************************************************************************
	STATIC FUNCTIONS
******************************************************************************/

// relocates food to random position on screen
static void reposition_food () {
	food.x = (rand () % (320 / 16)) * 16;
	food.y = (rand () % (240 / 16)) * 16;
}

// reset variables back to default so can replay
static void reset () {
	free_linkedlist (snake);
	free_linkedlist (turn);
	turn = NULL;
	reposition_food ();
	
	head_next_dir = DIR_EAST;
	countdown = 160;
	score = 0;
	
	head = snake = make_linkedlist_snake (0, 0, DIR_EAST, NULL);
	snake = make_linkedlist_snake (-16, 0, DIR_EAST, snake);
	snake = make_linkedlist_snake (-32, 0, DIR_EAST, snake);
	end = snake = make_linkedlist_snake (-48, 0, DIR_EAST, snake);
}

// called when player lost
static void lose () {
	extern int score_display, best_score; // in score.c
	score_display = score;
	if (score_display >= best_score) best_score = score_display;

	Mix_PlayChannel (-1, snd_crash, 0);
	reset ();
	stage_set (crash_get_stage ());
}

// checks to see whether the head is outside of the level
static boolean is_head_outside () {
	return (head->snake.x < 0 || head->snake.y < 0 || head->snake.x >= 320 || head->snake.y >= 240);
}

// for the given tail segment checks if it is on top of a turning point
static void tail_check_turn (LinkedList tail) {
	LinkedList tmp;

	// loop through all turn points
	for (tmp = turn; tmp != NULL; tmp = tmp->rest) {
		// if we are ontop of a turn point
		if (tail->snake.x == tmp->snake.x && tail->snake.y == tmp->snake.y) {
			tail->snake.dir = tmp->snake.dir; // then turn

			// if we are the end of the snake
			if (tail == end) {
				// reconstruct the entire list without this turn point
				LinkedList new_list = list_reconstruct_without (turn, tmp);
				free_linkedlist (turn); // free the old list
				turn = new_list; // hook up the new list
			}

			break;
		}
	}
}

// check to see if the head crashed with the tail
static boolean check_collision_with_self () {
	LinkedList tmp;
	
	for (tmp = snake; tmp != NULL; tmp = tmp->rest) {
		if (tmp == head) continue;

		if (tmp->snake.x == head->snake.x && tmp->snake.y == head->snake.y) {
			return true;
		}
	}

	return false;
}

// adds another segment to the end of the tail
static void add_to_tail () {
	int x = end->snake.x;
	int y = end->snake.y;
	int dir = end->snake.dir;

	switch (dir) {
		case DIR_NORTH: y += 16; break;
		case DIR_SOUTH: y -= 16; break;
		case DIR_EAST: x -= 16; break;
		case DIR_WEST: x += 16; break;
	}

	snake = make_linkedlist_snake (x, y, dir, snake);
	end = snake;
}

// move a snake segment based on its direction
static void move_snakesegment (SnakeSegment *seg) {
	switch (seg->dir) {
		case DIR_NORTH: seg->y -= speed; break;
		case DIR_SOUTH: seg->y += speed; break;
		case DIR_EAST: seg->x += speed; break;
		case DIR_WEST: seg->x -= speed; break;
	}
}

// handle cursor key presses
static void handle_input (void) {
	if (input_left_pressed) {
		input_left_pressed = false;

		if (head->snake.dir == DIR_EAST) return;

		head_next_dir = DIR_WEST;
	} else if (input_right_pressed) {
		input_right_pressed = false;

		if (head->snake.dir == DIR_WEST) return;

		head_next_dir = DIR_EAST;
	} else if (input_up_pressed) {
		input_up_pressed = false;

		if (head->snake.dir == DIR_SOUTH) return;

		head_next_dir = DIR_NORTH;
	} else if (input_down_pressed) {
		input_down_pressed = false;

		if (head->snake.dir == DIR_NORTH) return;

		head_next_dir = DIR_SOUTH;
	}
}

// the main menu update function
static void update (void) {
	LinkedList list;
	extern boolean running; // in sdl_snake.c

	if (input_window_closed || input_escape_pressed) running = false;
	
	if (countdown == 160 || countdown == 110 || countdown == 60) {
		Mix_PlayChannel (-1, snd_321, 0);
	} else if (countdown == 10) {
		Mix_PlayChannel (-1, snd_go, 0);
	}

	if (countdown >= 0) countdown --;
	if (countdown != -1) return; // lazy way to stop player from moving

	handle_input ();

	// if head is on grid
	if (head->snake.x % 16 == 0 && head->snake.y % 16 == 0) {
		if (head->snake.dir != head_next_dir) {	
			head->snake.dir = head_next_dir;
			turn = make_linkedlist_snake (head->snake.x, head->snake.y, head_next_dir, turn);
		}

		// head == pellet location; eat it
		if (head->snake.x == food.x && head->snake.y == food.y) {
			score += speed;
			Mix_PlayChannel (-1, snd_eat, 0);
			reposition_food ();
			add_to_tail ();
		}

		if (is_head_outside ()) {
			lose ();
			return;
		}
	}
	
	// loop through all snake parts
	for (list = snake; list != NULL; list = list->rest) {
		move_snakesegment (&list->snake); // GAH NULL POINTER EXCEPTION

		if (list == head) {
			if (check_collision_with_self ()) {
				lose (); // crash!
				return;
			}

			continue; // don't need to continue if we are at the head
		}

		tail_check_turn (list);
	}

	
}

// the main menu render function
static void render (void) {
	LinkedList list;

	draw_spritestrip (img_game_dots, food.x, food.y, 3);

	for (list = turn; list != NULL; list = list->rest) {
		draw_spritestrip (img_game_dots, list->snake.x, list->snake.y, 1);
	}

	for (list = snake; list != NULL; list = list->rest) {
		int sub, x, y;

		if (list == head) {
			sub = 0;
		} else if (list == end) {
			sub = 2;
		} else {
			sub = 1;
		}

		x = list->snake.x;
		x = x - (x % 8);

		y = list->snake.y;
		y = y - (y % 8);

		draw_spritestrip (img_game_dots, x, y, sub);
	}

	if (countdown != -1) {
		int subimg;

		if (countdown > 110) {
			subimg = 0; // 3
		} else if (countdown > 60) {
			subimg = 1; // 2
		} else if (countdown > 10) {
			subimg = 2; // 1
		} else {
			subimg = 3; // go
		}

		draw_spritestrip (img_countdown, 112, 96, subimg);
	}
}

/******************************************************************************
	stage_list.h FUNCTIONS
******************************************************************************/

Stage game_get_stage (void) {
	return make_stage (update, render);
}