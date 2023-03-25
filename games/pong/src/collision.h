/*
 * collision.h
 *
 * contains ball & paddle collision code
 */

#ifndef	COLLISION_H
#define	COLLISION_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "ball.h"

// The max positive and negative value that can be returned by ball_hit_any_paddle()
#define	PADDLE_HIT_POS_MAX	(PADDLE_HEIGHT / 2 + BALL_HEIGHT)

// Returns a value in the range [0, PADDLE_HEIGHT] that represents where on the paddle the ball hit
// If no paddle was hit, -1 is returned
int ball_hit_any_paddle(Ball *ball);

// Returns true if two rectangles are colliding
bool rect_hit_rect(SDL_Rect *r1, SDL_Rect *r2);

#endif
