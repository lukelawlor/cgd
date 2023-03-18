/*
 * collision.c
 *
 * contains ball & paddle collision code
 */

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "ball.h"
#include "collision.h"
#include "paddle.h"
#include "util/math.h"	// For clamp()

// Returns a value in the range [0, PADDLE_HEIGHT] that represents where on the paddle the ball hit
// If no paddle was hit, -1 is returned
static int ball_hit_paddle(SDL_Rect *ball_rect, Paddle *paddle);

// Returns a value in the range [0, PADDLE_HEIGHT] that represents where on the paddle the ball hit
// If no paddle was hit, -1 is returned
int ball_hit_any_paddle(Ball *ball)
{
	SDL_Rect ball_rect = {
		(int) ball->x,
		(int) ball->y,
		BALL_WIDTH,
		BALL_HEIGHT,
	};

	// Used to store return values from ball_hit_paddle()
	int value;
	value = ball_hit_paddle(&ball_rect, &g_left_paddle);
	if (value != -1)
		return value;
	value = ball_hit_paddle(&ball_rect, &g_right_paddle);
	if (value != -1)
		return value;
	return -1;
}

// Returns true if two rectangles are colliding
bool rect_hit_rect(SDL_Rect *r1, SDL_Rect *r2)
{
	return r1->x < r2->x + r2->w && r1->x + r1->w > r2->x && r1->y < r2->y + r2->h && r1->y + r1->h > r2->y;
}

// Returns a value in the range [0, PADDLE_HEIGHT] that represents where on the paddle the ball hit
// If no paddle was hit, -1 is returned
static int ball_hit_paddle(SDL_Rect *ball_rect, Paddle *paddle)
{
	SDL_Rect paddle_rect = {
		(int) paddle->x,
		(int) paddle->y,
		PADDLE_WIDTH,
		PADDLE_HEIGHT,
	};
	if (rect_hit_rect(ball_rect, &paddle_rect))
		return clamp((ball_rect->y - ball_rect->h / 2) - paddle->y, 0, PADDLE_HEIGHT);
	return -1;
}
