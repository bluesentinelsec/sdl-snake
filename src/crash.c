/*****************************************************************************
 * CRASH STAGE                                                               *
 * The screen that says CRASH!                                               *
 * See: stage_list.h                                                         *
 *****************************************************************************/

#include "input.h" // includes boolean.h
#include "stage_list.h"
#include "images.h" // includes sprite_strip.h

/******************************************************************************
	STATIC VARIABLES
******************************************************************************/

static int timer = 0;
static int subimg = 0;

/******************************************************************************
	STATIC FUNCTIONS
******************************************************************************/

// sets stage back to factory default (lulwut)
static void reset (void) {
	timer = 0;
	subimg = 0;
}

// the main menu update function
static void update (void) {
	extern boolean running; // in sdl_snake.c
	if (input_window_closed || input_escape_pressed) running = false;

	timer ++;

	if (timer % 25 == 0) subimg = (subimg + 1) % 2;
	
	if (timer >= 150) {
		reset ();
		transition_to (score_get_stage (), img_screen_crash, img_screen_score);
	}
}

// the main menu render function
static void render (void) {
	draw_spritestrip (img_crash, 0, 0, subimg);
}

/******************************************************************************
	stage_list.h FUNCTIONS
******************************************************************************/

Stage crash_get_stage (void) {
	return make_stage (update, render);
}