/*****************************************************************************
 * TRANSITION STAGE                                                          *
 * Plays an animation between two stages, then switches. USAGE: set images,  *
 * set stages, then use stage_set to this stage.                             *
 * See: stage_list.h                                                         *
 *****************************************************************************/

#include "stage_list.h" // includes stage.h
#include "sprite_strip.h" // includes SDL.h
#include <stdlib.h>
#include "images.h"

/******************************************************************************
	STATIC VARIABLES  
******************************************************************************/

static int timer = 0; // manages point in transition

/******************************************************************************
	EXTERNAL VARIABLES
******************************************************************************/

//the stage you are going to 
Stage stage_to;

// an image of the stage you are coming from
SDL_Surface *image_from = NULL;
// an image of the stage you are going to
SDL_Surface *image_to = NULL;

/******************************************************************************
	STAGE FUNCTIONS
******************************************************************************/

// resets the stage so it can be reused
static void reset (void) {
	timer = 0;
}

// logic
static void update (void) {
	timer += 40;

	if (timer > 40 * 30) {
		reset ();
		stage_set (stage_to);
		return;
	}

}

// draw to screen
static void render (void) {
	// this is some hacky shit
	SDL_Surface *screen = SDL_GetVideoSurface ();
	int x = timer % 40;
	int y = timer / 40;

	SDL_Rect yblock = {0, 0, 320, y * 8};
	SDL_Rect xblock = {0, y * 8, x * 8, 8};
	SDL_Rect xblock_dest = {0, y * 8, 0, 0};

	SDL_BlitSurface (image_from, NULL, screen, NULL);
	SDL_BlitSurface (image_to, &yblock, screen, NULL);
	SDL_BlitSurface (image_to, &xblock, screen, &xblock_dest);
}

Stage transition_get_stage (void) {
	return make_stage (update, render);
}