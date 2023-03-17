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
void paddle_update(Paddle *paddle)
{
	// Check for keyboard presses to move the paddle
	if (g_key_state[paddle->key_up])
		paddle->y -= PADDLE_SPEED;
	if (g_key_state[paddle->key_down])
		paddle->y += PADDLE_SPEED;

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
