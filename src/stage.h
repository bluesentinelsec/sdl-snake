/*****************************************************************************
 * STAGE HEADER                                                              *
 * A stage is a combination of an update and a render function which is      *
 * unique for a given screen or game area, eg. a main menu vs. the actual    *
 * game.                                                                     *
 * See: stage.c                                                              *
 *****************************************************************************/

#pragma once

// called once per tick
typedef void (*UpdateFunc)(void);
// called once per tick
typedef void (*RenderFunc)(void);

typedef struct {
	UpdateFunc update;
	RenderFunc render;
} Stage;

/**
 * Allocate a Stage on the stack given the necessary initialization, update and render
 * functions.
 */
Stage make_stage (UpdateFunc update, RenderFunc render);