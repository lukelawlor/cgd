/*
 * ball.c
 *
 * contains ball code
 */

#include <SDL2/SDL.h>

#include "ball.h"
#include "colors.h"
#include "main.h"	// For g_ren

#define	BALL_WIDTH	20
#define	BALL_HEIGHT	20
#define	BALL_X_MIN	ARENA_BORDER
#define	BALL_X_MAX	(WIN_WIDTH - ARENA_BORDER - BALL_WIDTH)
#define	BALL_Y_MIN	ARENA_BORDER
#define	BALL_Y_MAX	(WIN_HEIGHT - ARENA_BORDER - BALL_HEIGHT)

// Updates a ball
void ball_update(Ball *ball)
{
	ball->x += ball->xs;
	if (ball->x > BALL_X_MAX)
	{
		ball->x = BALL_X_MAX;
		ball->xs *= -1.1;
	}
	else if (ball->x < BALL_X_MIN)
	{
		ball->x = BALL_X_MIN;
		ball->xs *= -1.2;
	}
	ball->y += ball->ys;
	if (ball->y > BALL_Y_MAX)
	{
		ball->y = BALL_Y_MAX;
		ball->ys *= -1.3;
	}
	else if (ball->y < BALL_Y_MIN)
	{
		ball->y = BALL_Y_MIN;
		ball->ys *= -1.4;
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
