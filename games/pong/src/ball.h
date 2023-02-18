/*
 * ball.h
 *
 * contains ball code
 */

#ifndef	BALL_H
#define	BALL_H

#include "game.h"	// For ARENA_BORDER
#include "sdl.h"	// For WIN_WIDTH and WIN_HEIGHT

#define	BALL_WIDTH	20
#define	BALL_HEIGHT	20
#define	BALL_X_MIN	ARENA_BORDER
#define	BALL_X_MAX	(WIN_WIDTH - ARENA_BORDER - BALL_WIDTH)
#define	BALL_Y_MIN	ARENA_BORDER
#define	BALL_Y_MAX	(WIN_HEIGHT - ARENA_BORDER - BALL_HEIGHT)

typedef struct Ball{
	// Position
	double x;
	double y;

	// X speed
	double xs;
	
	// Y speed
	double ys;
} Ball;

// Updates a ball
void ball_update(Ball *ball);

// Draws a ball
void ball_draw(Ball *ball);

#endif
