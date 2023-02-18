/*
 * ball.h
 *
 * contains ball code
 */

#ifndef	BALL_H
#define	BALL_H

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
