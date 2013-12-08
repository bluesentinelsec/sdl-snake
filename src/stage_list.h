/*****************************************************************************
 * STAGE LIST HEADER                                                         *
 * A bunch of functions for getting pre-defined stages.                      *
 * See: stage.h, menu.c                                                      *
 *****************************************************************************/

#pragma once

#include "stage.h"
#include "sprite_strip.h"

Stage menu_get_stage (void);
Stage game_get_stage (void);
Stage difficulty_get_stage (void);
Stage crash_get_stage (void);
Stage transition_get_stage (void);
Stage score_get_stage (void);

// uhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
void stage_set (Stage stage);
void transition_to (Stage stage, SpriteStrip from_image, SpriteStrip to_image);