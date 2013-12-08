/*****************************************************************************
 * INPUT HEADER                                                              *
 * This input handler processes SDL_Event messages and stores them for easy  *
 * access.                                                                   *
 * See: input.c                                                              *
 *****************************************************************************/

#pragma once

#include "boolean.h"

// whether the window was requested to be closed (ie hitting the X)
boolean input_window_closed;

boolean input_left_pressed;
boolean input_right_pressed;
boolean input_up_pressed;
boolean input_down_pressed;

boolean input_escape_pressed;
boolean input_enter_pressed;

/**
 * Processes events from SDL_PollEvent.
 */
void process_sdl_events (void);

