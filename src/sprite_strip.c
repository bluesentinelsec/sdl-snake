/*****************************************************************************
 * SPRITE STRIP                                                              *
 * See: sprite_strip.h                                                       *
 *****************************************************************************/

#include <stdio.h>

#include "deb_mem.h"
#include "SDL.h"

#include "sprite_strip.h"

struct spritestrip {
	SDL_Surface *img; // the image
	int subimg_w; // the width of an individual subimage
};

/******************************************************************************
	STATIC FUNCTIONS
******************************************************************************/

// tries to load the image, optimize it, and set color key
static SDL_Surface *load_image (char *file) {
	SDL_Surface *img;
	SDL_Surface *opt;
	unsigned int magenta;

	img = SDL_LoadBMP (file);
	if (img == NULL) {
		fprintf (stderr, "ERROR: Could not load image '%s'!\n", file);
		exit (EXIT_FAILURE);
	}

	opt = SDL_DisplayFormat (img);
	magenta = SDL_MapRGB (opt->format, 255, 0, 255);
	if (opt == NULL) {
		fprintf (stderr, "ERROR: Failed to optimize image '%s'!\n", file);
		exit (EXIT_FAILURE);
	}
	SDL_SetColorKey (opt, SDL_SRCCOLORKEY, magenta);

	return opt;
}

/******************************************************************************
	CREATION AND DESTRUCTION
******************************************************************************/

SpriteStrip make_spritestrip (char *file, int subimage_width) {
	SpriteStrip ret = (SpriteStrip)dmalloc (sizeof (struct spritestrip));

	ret->img = load_image (file);
	if (subimage_width == 0) {
		ret->subimg_w = ret->img->w;
	} else {
		ret->subimg_w = subimage_width;
	}

	return ret;
}


void free_spritestrip (SpriteStrip sprite_strip) {
	SDL_FreeSurface (sprite_strip->img);
	dfree (sprite_strip);
}

/******************************************************************************
	DRAWING
******************************************************************************/

void draw_spritestrip (SpriteStrip sprite_strip, int x, int y, int subimage) {
	SDL_Surface *screen = SDL_GetVideoSurface ();
	SDL_Rect srcrect;
	SDL_Rect dstrect;

	srcrect.x = sprite_strip->subimg_w * subimage;
	srcrect.y = 0;
	srcrect.w = sprite_strip->subimg_w;
	srcrect.h = sprite_strip->img->h;

	dstrect.x = x;
	dstrect.y = y;
	// width and height don't matter

	SDL_BlitSurface (sprite_strip->img, &srcrect, screen, &dstrect);
}

/******************************************************************************
	PROPERTIES
******************************************************************************/

int spritestrip_get_subimage_width (SpriteStrip sprite_strip) {
	return sprite_strip->subimg_w;
}


int spritestrip_get_subimage_height (SpriteStrip sprite_strip) {
	return sprite_strip->img->h;
}

SDL_Surface *spritestrip_get_surface (SpriteStrip sprite_strip) {
	return sprite_strip->img;
}