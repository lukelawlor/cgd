/*
 * main.c
 *
 * contains the main function and game loop
 */

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "ball.h"
#include "colors.h"
#include "error.h"
#include "font.h"
#include "game.h"
#include "init.h"
#include "paddle.h"
#include "score.h"
#include "sdl.h"

int main(int argc, char **argv)
{
	if (game_init())
		return 1;

	// Initialize ball
	Ball ball = {
		.x = 80,
		.y = 80,
		.xs = 4,
		.ys = 0,
		.maxs = 25.1,
	};

	// Game loop
	SDL_Event e;
	bool game_running = true;
	while (game_running)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				game_running = false;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_Q:
					// Quit the game when q is pressed
					game_running = false;
					break;
				default:
					break;
				}
			}
		}

		// Update game objects
		paddle_update(&g_left_paddle);
		paddle_update(&g_right_paddle);
		ball_update(&ball);

		// Clear the screen with the background color
		SDL_SetRenderDrawColor(
			g_ren,
			WIN_COLOR_R,
			WIN_COLOR_G,
			WIN_COLOR_B,
			255
		);
		SDL_RenderClear(g_ren);

		// Draw game objects
		paddle_draw(&g_left_paddle);
		paddle_draw(&g_right_paddle);
		ball_draw(&ball);

		// Draw the scoreboard
		score_draw();
		
		// Update screen
		SDL_RenderPresent(g_ren);
	}
	game_quit();
	return 0;
}
