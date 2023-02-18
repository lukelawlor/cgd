/*
 * collision.c
 *
 * contains ball & paddle collision code
 */

#include <SDL2/SDL.h>

#include "ball.h"
#include "collision.h"
#include "paddle.h"

// Returns true if the ball collides with a single paddle
static bool ball_hit_paddle(SDL_Rect *ball_rect, Paddle *paddle);

// Returns true if the ball collides with any paddle in the game
bool ball_hit_any_paddle(Ball *ball)
{
	SDL_Rect ball_rect = {
		(int) ball->x,
		(int) ball->y,
		BALL_WIDTH,
		BALL_HEIGHT,
	};
	return ball_hit_paddle(&ball_rect, &g_left_paddle) || ball_hit_paddle(&ball_rect, &g_right_paddle);
}

// Returns true if two rectangles are colliding
bool rect_hit_rect(SDL_Rect *r1, SDL_Rect *r2)
{
	return r1->x < r2->x + r2->w && r1->x + r1->w > r2->x && r1->y < r2->y + r2->h && r1->y + r1->h > r2->y;
}

// Returns true if the ball collides with a single paddle
static bool ball_hit_paddle(SDL_Rect *ball_rect, Paddle *paddle)
{
	SDL_Rect paddle_rect = {
		(int) paddle->x,
		(int) paddle->y,
		PADDLE_WIDTH,
		PADDLE_HEIGHT,
	};
	return rect_hit_rect(ball_rect, &paddle_rect);
}
