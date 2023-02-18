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
#include "main.h"
#include "paddle.h"

// Renderer flags
#define	REN_FLAGS	(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)

// SDL objects
SDL_Window *g_win = NULL;
SDL_Renderer *g_ren = NULL;

// Get the keyboard state
const Uint8 *g_key_state = NULL;

int main(int argc, char **argv)
{
	int exit_code = 1;

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		PERR("SDL_Init failed. %s\n", SDL_GetError());
		goto l_exit;
	}

	// Create the window
	g_win = SDL_CreateWindow(
		"PONG",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if (g_win == NULL)
	{
		PERR("SDL_CreateWindow like failed or stuff. %s\n", SDL_GetError());
		goto l_exit;
	}

	// Create the renderer
	g_ren = SDL_CreateRenderer(
		g_win,
		-1,
		REN_FLAGS
	);
	if (g_ren == NULL)
	{
		PERR("SDL_CreateRenderer failed. %s\n", SDL_GetError());
		goto l_exit;
	}
	
	// Get keyboard state
	g_key_state = SDL_GetKeyboardState(NULL);

	// Initialize game objects
	Ball ball = {
		80,
		80,
		4,
		4,
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
					game_running = false;
					break;
				default:
					break;
				}
			}
		}

		paddle_update(&g_left_paddle, true);
		paddle_update(&g_right_paddle, false);
		ball_update(&ball);

		SDL_SetRenderDrawColor(
			g_ren,
			WIN_COLOR_R,
			WIN_COLOR_G,
			WIN_COLOR_B,
			255
		);
		SDL_RenderClear(g_ren);

		paddle_draw(&g_left_paddle);
		paddle_draw(&g_right_paddle);
		ball_draw(&ball);

		SDL_RenderPresent(g_ren);
	}

	exit_code = 0;
l_exit:
	SDL_DestroyWindow(g_win);
	SDL_DestroyRenderer(g_ren);
	SDL_Quit();
	return exit_code;
}
