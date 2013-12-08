/*****************************************************************************
 * DIFFICULTY STAGE                                                          *
 * A bunch of functions which defines the difficulty choosing stage.         *
 * See: stage_list.h                                                         *
 *****************************************************************************/

#include "input.h" // includes boolean.h
#include "stage_list.h"
#include "images.h" // includes sprite_strip.h
#include <stdio.h>
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
	extern int speed; // in game.c

	if (input_window_closed || input_escape_pressed) running = false;
	
	if (input_up_pressed) {
		input_up_pressed = false;
		Mix_PlayChannel (-1, snd_menu_blip, 0);
		choice = (choice == 0 ? 2 : choice - 1);
	}

	if (input_down_pressed) {
		input_down_pressed = false;
		Mix_PlayChannel (-1, snd_menu_blip, 0);
		choice = (choice + 1) % 3;
	}

	if (input_enter_pressed) {	
		Mix_PlayChannel (-1, snd_menu_select, 0);

		input_enter_pressed = false;

		switch (choice) {
			case 0: speed = 1; break;
			case 1: speed = 2; break;
			case 2: speed = 4; break;
		}

		reset ();
		transition_to (game_get_stage (), img_screen_diff, img_screen_game);
	}
}

// the main menu render function
static void render (void) {
	draw_spritestrip (img_diff_easy, 88, 32, (choice == 0 ? 1 : 0));
	draw_spritestrip (img_diff_norm, 88, 32 + 56, (choice == 1 ? 1 : 0));
	draw_spritestrip (img_diff_hard, 88, 32 + 56 + 56, (choice == 2 ? 1 : 0));
}

/******************************************************************************
	stage_list.h FUNCTIONS
******************************************************************************/

Stage difficulty_get_stage (void) {
	return make_stage (update, render);
}