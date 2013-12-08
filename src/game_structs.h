/*****************************************************************************
 * SEVERAL GAME STRUCTURES                                                   *
 * A bunch of structures used by the game stage (game.c), including          *
 * individual snake parts (SnakeSegment) and a general Point struct.         *
 * See: game_structs.c, game.c                                               *
 *****************************************************************************/

#pragma once

enum Direction {
	DIR_NORTH = 0, DIR_EAST = 1, DIR_SOUTH = 2, DIR_WEST = 3
};

typedef struct {
	int x;
	int y;
	int dir;
} SnakeSegment;

typedef struct {
	int x;
	int y;
} Point;