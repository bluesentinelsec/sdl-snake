/*****************************************************************************
 * SCORE STAGE                                                               *
 * Shows the score and high schore.                                          *
 * See: stage_list.h                                                         *
 *****************************************************************************/

#include "input.h" // includes boolean.h
#include "stage_list.h"
#include "images.h" // includes sprite_strip.h
#include <stdio.h>

/******************************************************************************
	EXTERNAL VARIABLES
******************************************************************************/

int best_score = 0; // the highest score so far
int score_display = 0; // the score just gotten

/******************************************************************************
	STATIC FUNCTIONS
******************************************************************************/

// draws the given number to the screen using img_numbers
static void draw_number (int number, int x, int y) {
	char str[5];
	int i;

	if (number >= 9999 || number < 0) {
		sprintf (str, "9999");
	} else {
		sprintf (str, "%d", number);
	}

	for (i = 0; str[i] != '\0'; i++) {
		draw_spritestrip (img_numbers, x + 32 * i, y, str[i] - '0');
	}
}

// the update function
static void update (void) {
	extern boolean running; // in sdl_snake.c
	if (input_window_closed || input_escape_pressed) running = false;

	if (input_enter_pressed) {
		input_enter_pressed = false;
		transition_to (menu_get_stage (), img_screen_score, img_screen_menu);
	}

	// uh... any key?
}

// the render function
static void render (void) {
	draw_spritestrip (img_score, 8, 48, 0);
	draw_spritestrip (img_best, 8, 240 - 40 - 48, 0);
	draw_number (score_display, 192, 48);
	draw_number (best_score, 192, 240 - 40 - 48);
}

/******************************************************************************
	stage_list.h FUNCTIONS
******************************************************************************/

Stage score_get_stage (void) {
	return make_stage (update, render);
}