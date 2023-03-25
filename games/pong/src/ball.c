/*
 * ball.c
 *
 * contains ball code
 */

#include <SDL2/SDL.h>

#include <stdlib.h>

#include "ball.h"
#include "collision.h"	// For ball_hit_any_paddle()
#include "colors.h"
#include "error.h"
#include "game.h"	// For ARENA_BORDER
#include "paddle.h"	// For PADDLE_HEIGHT
#include "score.h"
#include "sdl.h"	// For g_ren, WIN_WIDTH, & WIN_HEIGHT
#include "texture.h"	// For tex_ball
#include "util/math.h"	// For sign()

// Resets the ball's position to the center of the game
static void ball_reset(Ball *ball);

// Updates a ball
void ball_update(Ball *ball)
{
	// Randomly move the ball
#if 0 
	ball->x += (((rand() % 101) / 100.0) - 0.5) * 8;
	ball->y += (((rand() % 101) / 100.0) - 0.5) * 8;
#endif

	// Handle paddle collisions
	int pos;

	if ((pos = ball_hit_any_paddle(ball)) != -1)
	{
		// Reverse the ball's speed
		int ball_xs_sign = signf(ball->xs);
		ball->xs = -ball_xs_sign;

		// Move the ball out of the paddle
		while (ball_hit_any_paddle(ball) != -1)
			ball->x += ball->xs;

		// Calculate the new x & y speeds of the ball
		// This depends on the pos returned by the initial call to ball_hit_any_paddle()
		double edge_factor = (double) pos / PADDLE_HIT_POS_MAX;
		double edge_inverse = 1 - fabs(edge_factor);

		ball->xs = -ball_xs_sign * ball->maxs * edge_inverse;
		ball->ys = ball->maxs * edge_factor;
	}

	// Move the ball and bounce it off of the game world border

	// Touching the right side
	ball->x += ball->xs;
	if (ball->x > BALL_X_MAX)
	{
		ball->x = BALL_X_MAX;
		ball->xs *= -1;
		ball_reset(ball);
		g_score.pts_right++;
	}

	// Touching the left side
	else if (ball->x < BALL_X_MIN)
	{
		ball->x = BALL_X_MIN;
		ball->xs *= -1;
		ball_reset(ball);
		g_score.pts_left++;
	}

	// Touching the bottom side
	ball->y += ball->ys;
	if (ball->y > BALL_Y_MAX)
	{
		ball->y = BALL_Y_MAX;
		ball->ys *= -1;
	}

	// Touching the top side
	else if (ball->y < BALL_Y_MIN)
	{
		ball->y = BALL_Y_MIN;
		ball->ys *= -1;
	}
}

// Draws a ball
void ball_draw(Ball *ball)
{
	SDL_Rect drect = {ball->x, ball->y, BALL_WIDTH, BALL_HEIGHT};
	SDL_Rect srect = {0, 0, 100, 100};
	SDL_RenderCopy(g_ren, tex_ball, &srect, &drect);
	// Draw a rectangle
#if 0
	SDL_SetRenderDrawColor(
		g_ren,
		BALL_COLOR_R,
		BALL_COLOR_G,
		BALL_COLOR_B,
		255
	);
	SDL_RenderFillRect(g_ren, &drect);
#endif
}

// Resets the ball's position to the center of the game
static void ball_reset(Ball *ball)
{
	ball->x = WIN_WIDTH / 2;
	ball->y = WIN_HEIGHT / 2;
}
