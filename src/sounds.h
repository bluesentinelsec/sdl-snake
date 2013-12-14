/*****************************************************************************
 * SOUNDS HEADER                                                             *
 * Provides easy access to all sounds.                                       *
 * See: sdl_snake.c                                                          *
 *****************************************************************************/

#pragma once

#ifdef _WIN32 // STUPID WINDOWS
    #include "SDL_mixer.h"
#else
    #include "SDL/SDL_mixer.h"
#endif

Mix_Chunk *snd_menu_blip;
Mix_Chunk *snd_menu_select;
Mix_Chunk *snd_crash;
Mix_Chunk *snd_eat;
Mix_Chunk *snd_321;
Mix_Chunk *snd_go;