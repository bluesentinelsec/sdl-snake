/*****************************************************************************
 * SDL SNAKE                                                                 *
 * Snake in C with SDL and snakiness and yeah!                               *
 * See: README.txt, LICENSE.txt                                              *
 *****************************************************************************/

// TODO better error checking and handling all around
// TODO add load_images to images.h?
// TODO add reset/init to stages?
// TODO more comments!
// TODO interface between stages
// TODO get rid of magic numbers

#include <stdio.h>
#include <time.h>

#include "SDL.h" // should be included before everything else
#include "deb_mem.h" // includes stdlib.h

#include "sounds.h" // includes SDL_mixer.h
#include "images.h" // includes sprite_strip.h
#include "stage_list.h" // includes stage.h
#include "input.h" // includes boolean.h
#include "list.h" // includes game_structs.h

/******************************************************************************
	STATIC FUNCTION PROTOTYPES
******************************************************************************/

// initialize the game; is run right after SDL_Init
static void init (void);

// loads all the images
static void load_all_images (void);

// attempts to load a sound; terminates if can't
static Mix_Chunk *load_sound (char *file);

// load all needed sound files
static void load_all_sounds (void);

// the main game loop; run after init; calls render and update; regulates fps
static void main_loop (void);

// free any allocated resources; is run after main_loop stops
static void cleanup (void);

/******************************************************************************
	STATIC VARIABLES
******************************************************************************/

static SDL_Surface *screen = NULL; // the screen we are drawing to

// screen dimensions and whatnot
static const int SCREEN_WIDTH = 320;
static const int SCREEN_HEIGHT = 240;
static const int SCREEN_BPP = 32;
static const int SCREEN_FLAGS = SDL_SWSURFACE;
static const char *SCREEN_TITLE = "SDL Snake";

static const int TARGET_FPS = 50;

static Stage cur_stage;

/******************************************************************************
	GENERAL VARIABLES
******************************************************************************/

boolean running = true; // whether the main_loop is looping or not

/******************************************************************************
	UHHHHHHHHHHHHHHHHHH (stage_list.h)
******************************************************************************/

void stage_set (Stage stage) {
	cur_stage = stage;
}


void transition_to (Stage stage, SpriteStrip from_image, SpriteStrip to_image) {
	extern SDL_Surface *image_from; // in transition.c
	extern SDL_Surface *image_to; // in transition.c
	extern Stage stage_to; // in transition.c

	stage_to = stage;
	image_from = spritestrip_get_surface (from_image);
	image_to = spritestrip_get_surface (to_image);

	stage_set (transition_get_stage ());
}

/******************************************************************************
	ACTAUL STATIC FUNCTION
******************************************************************************/

static void init (void) {
	extern LinkedList head; // in game.c
	extern LinkedList snake; // in game.c
	extern LinkedList end; // in game.c
	extern Point food; // in game.c

	srand (time (NULL)); // init RNG

	screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SCREEN_FLAGS);
	if (screen == NULL) {
		fprintf (stderr, "ERROR: %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}

	SDL_WM_SetCaption (SCREEN_TITLE, NULL);

	if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		fprintf (stderr, "ERROR: %s\n", Mix_GetError ());
		exit (EXIT_FAILURE);
	}

	load_all_images ();
	load_all_sounds ();

	head = snake = make_linkedlist_snake (0, 0, DIR_EAST, NULL);
	snake = make_linkedlist_snake (-16, 0, DIR_EAST, snake);
	snake = make_linkedlist_snake (-32, 0, DIR_EAST, snake);
	end = snake = make_linkedlist_snake (-48, 0, DIR_EAST, snake);

	food.x = (rand () % (SCREEN_WIDTH / 16)) * 16;
	food.y = (rand () % (SCREEN_HEIGHT / 16)) * 16;

	transition_to (menu_get_stage (), img_background, img_screen_menu);
}


static void load_all_images (void) {
	img_background = make_spritestrip ("images/background.bmp", 0);

	img_menu_snake = make_spritestrip ("images/menu-snake.bmp", 0);
	img_menu_play = make_spritestrip ("images/menu-play.bmp", 136);
	img_menu_quit = make_spritestrip ("images/menu-quit.bmp", 136);

	img_diff_easy = make_spritestrip ("images/diff-easy.bmp", 136);
	img_diff_norm = make_spritestrip ("images/diff-norm.bmp", 136);
	img_diff_hard = make_spritestrip ("images/diff-hard.bmp", 136);

	img_game_dots = make_spritestrip ("images/dots.bmp", 16);
	img_countdown = make_spritestrip ("images/countdown.bmp", 88);
	img_crash = make_spritestrip ("images/crash.bmp", 320);

	img_screen_menu = make_spritestrip ("images/screens/menu.bmp", 0);
	img_screen_diff = make_spritestrip ("images/screens/diff-select.bmp", 0);
	img_screen_game = make_spritestrip ("images/screens/game.bmp", 0);
	img_screen_crash = make_spritestrip ("images/screens/crash-screen.bmp", 0);
	img_screen_score = make_spritestrip ("images/screens/score.bmp", 0);

	img_numbers = make_spritestrip ("images/numbers.bmp", 24);
	img_best = make_spritestrip ("images/best.bmp", 0);
	img_score = make_spritestrip ("images/score.bmp", 0);
}


static Mix_Chunk *load_sound (char *file) {
	Mix_Chunk *ret = Mix_LoadWAV (file);

	if (ret == NULL) {
		fprintf (stderr, "ERROR: Could not load sound '%s'!\n", file);
		exit (EXIT_FAILURE);
	}

	return ret;
}


static void load_all_sounds (void) {
	snd_menu_blip = load_sound ("sounds/switch1.wav");
	snd_menu_select = load_sound ("sounds/select1.wav");
	snd_crash = load_sound ("sounds/crash2.wav");
	snd_eat = load_sound ("sounds/eat1.wav");
	snd_321 = load_sound ("sounds/321.wav");
	snd_go = load_sound ("sounds/go2.wav");
}


static void main_loop (void) {
	unsigned int last_second = 0;
	unsigned int ticks = 0;
	unsigned int interval = 1000 / TARGET_FPS; // want 50 fps

	while (running) {
		unsigned int time = SDL_GetTicks ();

		if (time >= last_second + 1000) { // if one second has passed
			// print out fps
			//fprintf (stderr, "FPS: %d\n", ticks); // DEBUG
			ticks = 0;
			last_second += 1000;
		}

		if (time >= last_second + interval * ticks) {
			ticks++;
			process_sdl_events ();
			cur_stage.update ();
			draw_spritestrip (img_background, 0, 0, 0);
			cur_stage.render ();
			SDL_Flip (screen);
		}
	}
}


static void cleanup (void) {
	extern LinkedList snake; // in game.c
	extern LinkedList turn; // in game.c

	free_spritestrip (img_background);

	free_spritestrip (img_menu_snake);
	free_spritestrip (img_menu_play);
	free_spritestrip (img_menu_quit);

	free_spritestrip (img_diff_easy);
	free_spritestrip (img_diff_norm);
	free_spritestrip (img_diff_hard);

	free_spritestrip (img_game_dots);
	free_spritestrip (img_countdown);
	free_spritestrip (img_crash);

	free_spritestrip (img_screen_menu);
	free_spritestrip (img_screen_crash);
	free_spritestrip (img_screen_diff);
	free_spritestrip (img_screen_game);
	free_spritestrip (img_screen_score);

	free_spritestrip (img_numbers);
	free_spritestrip (img_score);
	free_spritestrip (img_best);

	free_linkedlist (snake);
	free_linkedlist (turn);

	Mix_FreeChunk (snd_menu_blip);
	Mix_FreeChunk (snd_menu_select);
	Mix_FreeChunk (snd_crash);
	Mix_FreeChunk (snd_eat);
	Mix_FreeChunk (snd_321);
	Mix_FreeChunk (snd_go);

	Mix_CloseAudio ();

	//print_unfreed ();
}

/******************************************************************************
	MAIN ENTRY POINT
******************************************************************************/

int main (int argc, char **argv) {
	SDL_Init (SDL_INIT_EVERYTHING); // check for return value?

	init ();
	main_loop ();
	cleanup ();

	SDL_Quit ();
	return 0;
}