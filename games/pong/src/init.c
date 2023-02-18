/*
 * init.c
 *
 * contains game initialization code
 */

#include <SDL2/SDL.h>

#include "error.h"
#include "game.h"
#include "init.h"
#include "paddle.h"
#include "sdl.h"

// Initializes everything needed to start the game loop, returns nonzero on error
int game_init(void)
{
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		PERR("SDL_Init failed. %s\n", SDL_GetError());
		goto l_error;
	}

	// Create the window
	g_win = SDL_CreateWindow(
		"pong sick",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if (g_win == NULL)
	{
		PERR("SDL_CreateWindow like failed or stuff. %s\n", SDL_GetError());
		goto l_error;
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
		goto l_error;
	}
	
	// Get keyboard state
	g_key_state = SDL_GetKeyboardState(NULL);

	// Initialize game objects
	g_left_paddle = (Paddle) {
		.x = ARENA_BORDER,
		.y = ARENA_BORDER,
	};
	g_right_paddle = (Paddle) {
		.x = WIN_WIDTH - ARENA_BORDER - PADDLE_WIDTH,
		.y = ARENA_BORDER,
	};

	// Success
	return 0;
l_error:
	game_quit();
	return 1;
}

// Undoes initialization steps done by game_init()
void game_quit(void)
{
	SDL_DestroyWindow(g_win);
	SDL_DestroyRenderer(g_ren);
	SDL_Quit();
}
