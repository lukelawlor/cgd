/*
 * paddle.h
 *
 * contains code for the pong paddle
 */

#ifndef	PADDLE_H
#define	PADDLE_H

#include <stdbool.h>

// Paddle settings
#define	PADDLE_SPEED	16
#define	PADDLE_WIDTH	(120*4)
#define	PADDLE_HEIGHT	(40*8*2)
#define	PADDLE_Y_MIN	ARENA_BORDER
#define	PADDLE_Y_MAX	(WIN_HEIGHT - ARENA_BORDER - PADDLE_HEIGHT)

// Paddle type
typedef struct Paddle{
	// Position
	double x;
	double y;
} Paddle;

extern Paddle g_left_paddle;
extern Paddle g_right_paddle;

// Updates a paddle
void paddle_update(Paddle *paddle, bool is_left_paddle);

// Draws a paddle
void paddle_draw(Paddle *paddle);

#endif
