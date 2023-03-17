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
#include "score.h"
#include "sdl.h"	// For g_ren, WIN_WIDTH, & WIN_HEIGHT

// Resets the ball's position to the center of the game
static void ball_reset(Ball *ball);

// Updates a ball
void ball_update(Ball *ball)
{
	ball->x += (((rand() % 101) / 100.0) - 0.5) * 8;
	ball->y += (((rand() % 101) / 100.0) - 0.5) * 8;

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

	// Handle paddle collisions
	if (ball_hit_any_paddle(ball))
	{
		ball->xs *= -1;
		ball->ys *= -1;
		ball->x += ball->xs;
		ball->y += ball->ys;
	}
}

// Draws a ball
void ball_draw(Ball *ball)
{
	SDL_SetRenderDrawColor(
		g_ren,
		BALL_COLOR_R,
		BALL_COLOR_G,
		BALL_COLOR_B,
		255
	);
	SDL_Rect drect = {ball->x, ball->y, 20, 20};
	SDL_RenderFillRect(g_ren, &drect);
}

// Resets the ball's position to the center of the game
static void ball_reset(Ball *ball)
{
	ball->x = WIN_WIDTH / 2;
	ball->y = WIN_HEIGHT / 2;
}
