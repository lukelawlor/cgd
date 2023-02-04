#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "error.h"

// Window dimensions
#define	WIN_WIDTH	800
#define	WIN_HEIGHT	800

// Renderer flags
#define	REN_FLAGS	(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)

// SDL objects
SDL_Window *g_win = NULL;
SDL_Renderer *g_ren = NULL;

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
			}
		}
		SDL_SetRenderDrawColor(g_ren, 255, 200, 100, 255);
		SDL_RenderClear(g_ren);
		SDL_RenderPresent(g_ren);
	}

	exit_code = 0;
l_exit:
	SDL_DestroyWindow(g_win);
	SDL_DestroyRenderer(g_ren);
	SDL_Quit();
	return exit_code;
}
