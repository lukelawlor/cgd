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

// Returns true if the ball is colliding with a paddle
bool ball_hit_any_paddle(Ball *ball);

// Returns true if two rectangles are colliding
bool rect_hit_rect(SDL_Rect *r1, SDL_Rect *r2);

#endif
