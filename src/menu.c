/*****************************************************************************
 * MENU STAGE                                                                *
 * A bunch of functions which defines main menu behavior.                    *
 * See: stage_list.h                                                         *
 *****************************************************************************/

#include "input.h" // includes boolean.h
#include "stage_list.h"
#include "images.h" // includes sprite_strip.h
#include "sounds.h" // includes SDL_mixer.h

/******************************************************************************
	STATIC VARIABLES
******************************************************************************/

static int choice = 0;

/******************************************************************************
	STATIC FUNCTIONS
******************************************************************************/

static void reset (void) {
	choice = 0;
}

// the main menu update function
static void update (void) {
	extern boolean running; // in sdl_snake.c
	if (input_window_closed || input_escape_pressed) running = false;
	
	if (input_left_pressed) {
		input_left_pressed = false;
		choice --;
		if (choice < 0) choice = 1;
		Mix_PlayChannel (-1, snd_menu_blip, 0);
	}

	if (input_right_pressed) {
		input_right_pressed = false;
		choice = (choice + 1) % 2;
		Mix_PlayChannel (-1, snd_menu_blip, 0);
	}

	if (input_enter_pressed) {
		input_enter_pressed = false;

		Mix_PlayChannel (-1, snd_menu_select, 0);

		if (choice == 1) {
			running = false;
		} else if (choice == 0) {
			reset ();
			transition_to (difficulty_get_stage (), img_screen_menu, img_screen_diff);
		}
	}
}

// the main menu render function
static void render (void) {
	draw_spritestrip (img_menu_snake, 8, 8, 0);
	draw_spritestrip (img_menu_play, 16, 240 - 24 - 56, (choice == 0 ? 1 : 0));
	draw_spritestrip (img_menu_quit, 320 - 136 - 16, 240 - 24 - 56, (choice == 1 ? 1 : 0));
}

/******************************************************************************
	stage_list.h FUNCTIONS
******************************************************************************/

Stage menu_get_stage (void) {
	return make_stage (update, render);
}