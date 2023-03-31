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
#include "timestep.h"
#include "util/math.h"	// For sign()

// Resets the ball's position to the center of the game
static void ball_reset(Ball *ball);

// Updates a ball
void ball_update(Ball *ball)
{
	// Randomly move the ball
#if 1
	ball->x += (((rand() % 101) / 100.0) - 0.5) * 8 * g_ts;
	ball->y += (((rand() % 101) / 100.0) - 0.5) * 8 * g_ts;
#endif

	// Move the ball and bounce it off of the game world border
	bool should_reset = false;

	// Pointer to point value to increase when the ball should reset
	int *score_to_increase = NULL;

	// Touching the right side
	ball->x += ball->xs * g_ts;
	if (ball->x > BALL_X_MAX)
	{
		ball->x = BALL_X_MAX;
		score_to_increase = &g_score.pts_right;
		should_reset = true;
	}

	// Touching the left side
	else if (ball->x < BALL_X_MIN)
	{
		ball->x = BALL_X_MIN;
		score_to_increase = &g_score.pts_left;
		should_reset = true;
	}

	// Touching the bottom side
	ball->y += ball->ys * g_ts;
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

		ball->xs = clampf(ball->max_speed * edge_inverse, ball->min_xs, ball->max_speed) * -ball_xs_sign;
		ball->ys = ball->max_speed * edge_factor;
	}
	else if (should_reset)
	{
		++(*score_to_increase);
		ball_reset(ball);
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
	ball->xs *= -1;
	ball->x = WIN_WIDTH / 2;
	ball->y = WIN_HEIGHT / 2;
}
