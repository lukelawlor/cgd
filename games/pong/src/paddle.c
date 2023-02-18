/*
 * paddle.c
 *
 * contains code for the pong paddle
 */

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "colors.h"
#include "game.h"	// For ARENA_BORDER
#include "keys.h"
#include "sdl.h"	// For g_ren and g_key_state
#include "paddle.h"
#include "util/math.h"	// For clamp()

Paddle g_left_paddle;
Paddle g_right_paddle;

// Updates a paddle
void paddle_update(Paddle *paddle, bool is_left_paddle)
{
	// Check for keyboard presses to move the paddle
	if (is_left_paddle)
	{
		if (g_key_state[KEY_PADDLE_LEFT_UP])
			paddle->y -= PADDLE_SPEED;
		if (g_key_state[KEY_PADDLE_LEFT_DOWN])
			paddle->y += PADDLE_SPEED;
	}
	else
	{
		if (g_key_state[KEY_PADDLE_RIGHT_UP])
			paddle->y -= PADDLE_SPEED;
		if (g_key_state[KEY_PADDLE_RIGHT_DOWN])
			paddle->y += PADDLE_SPEED;
	}

	// Keep the paddle within the game world
	paddle->y = clamp(
		paddle->y,
		PADDLE_Y_MIN,
		PADDLE_Y_MAX
	);
}

// Draws a paddle
void paddle_draw(Paddle *paddle)
{
	SDL_SetRenderDrawColor(
		g_ren,
		PADDLE_COLOR_R,
		PADDLE_COLOR_G,
		PADDLE_COLOR_B,
		255
	);
	SDL_Rect drect = {
		(int) paddle->x,
		(int) paddle->y,
		PADDLE_WIDTH,
		PADDLE_HEIGHT,
	};
	SDL_RenderFillRect(g_ren, &drect);
}
