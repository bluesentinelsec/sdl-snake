/*****************************************************************************
 * INPUT                                                                     *
 * See: input.h                                                              *
 *****************************************************************************/

#if defined _WIN32 || defined __APPLE__
    #include <SDL.h>
#else
    #include "SDL/SDL.h"
#endif

#include "input.h"
#include "boolean.h"

/******************************************************************************
	input.h VARIABLES
******************************************************************************/

boolean input_window_closed = false;

boolean input_left_pressed = false;
boolean input_right_pressed = false;
boolean input_up_pressed = false;
boolean input_down_pressed = false;

boolean input_escape_pressed = false;
boolean input_enter_pressed = false;

/******************************************************************************
	STATIC FUNCTIONS
******************************************************************************/

// act on given key press
static void process_key_down (SDLKey key) {
	switch (key) {
		case SDLK_LEFT: input_left_pressed = true; break;
		case SDLK_RIGHT: input_right_pressed = true; break;
		case SDLK_UP: input_up_pressed = true; break;
		case SDLK_DOWN: input_down_pressed = true; break;
		case SDLK_ESCAPE: input_escape_pressed = true; break;
		case SDLK_RETURN: input_enter_pressed = true; break;
	}
}

// act on given key release
static void process_key_up (SDLKey key) {
	switch (key) {
		case SDLK_LEFT: input_left_pressed = false; break;
		case SDLK_RIGHT: input_right_pressed = false; break;
		case SDLK_UP: input_up_pressed = false; break;
		case SDLK_DOWN: input_down_pressed = false; break;
		case SDLK_ESCAPE: input_escape_pressed = false; break;
		case SDLK_RETURN: input_enter_pressed = false; break;
	}
}

/******************************************************************************
	input.h FUNCTIONS
******************************************************************************/

void process_sdl_events () {
	SDL_Event sdl_event;
	while (SDL_PollEvent (&sdl_event)) {
		switch (sdl_event.type) {
			case SDL_QUIT:
				input_window_closed = true;
				break;
			case SDL_KEYDOWN:
				process_key_down (sdl_event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				process_key_up (sdl_event.key.keysym.sym);
				break;
		}
	}
}
