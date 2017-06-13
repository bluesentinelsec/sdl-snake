/*****************************************************************************
 * SPRITE STRIP HEADER                                                       *
 * A SpriteStrip is a wrapper around an SDL_Surface which allows for         *
 * multiple subimages of the same width along a horizontal line to be packed *
 * into one file, eg. animations, and then selectively drawn. They are       *
 * always allocated on the heap.                                             *
 * See: sprite_strip.c                                                       *
 *****************************************************************************/

#pragma once

#if defined _WIN32 || defined __APPLE__
    #include <SDL.h>
#else
    #include "SDL/SDL.h"
#endif

// make SpriteStrip an opaque type
struct spritestrip;
typedef struct spritestrip * SpriteStrip;

/******************************************************************************
	CREATION AND DESTRUCTION
******************************************************************************/

/**
 * Make a SpriteStrip on the heap given an image and subimage width. If
 * subimage_width is 0 then the image's width is used. Must be freed later on!
 */
SpriteStrip make_spritestrip (char *file, int subimage_width);


/**
 * Given a SpriteStrip that has been allocated on the heap, frees memory used
 * by the image and the structure.
 */
void free_spritestrip (SpriteStrip sprite_strip);

/******************************************************************************
	DRAWING
******************************************************************************/

/**
 * Draws the the given subimage of the given SpriteStrip at the given position
 * to the SDL_Surface returned by SDL_GetVideoSurface ().
 */
void draw_spritestrip (SpriteStrip sprite_strip, int x, int y, int subimage);

/******************************************************************************
	PROPERTIES
******************************************************************************/

int spritestrip_get_subimage_width (SpriteStrip sprite_strip);
int spritestrip_get_subimage_height (SpriteStrip sprite_strip);
SDL_Surface *spritestrip_get_surface (SpriteStrip sprite_strip);
