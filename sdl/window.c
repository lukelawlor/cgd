/*
 * window.c
 *
 * This program creates a new window, waits for 5 seconds, and then exits.
 */

#include <stdio.h>

#include <SDL2/SDL.h>

#include "error.h"

int main(int argc, char **argv)
{
	int exit_code = 1;

	// The window
	SDL_Window *win = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		PERR("SDL_Init failed. %s", SDL_GetError());
		goto l_exit;
	}
	
	// Create the window
	const char *win_name = "good window";
	const int win_width = 640;
	const int win_height = 480;
	win = SDL_CreateWindow(
		win_name,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		win_width,
		win_height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if (win == NULL)
	{
		PERR("SDL_CreateWindow failed. %s", SDL_GetError());
		goto l_exit;
	}

	// Wait for 5 seconds so the window doesn't immediately close when our program ends
	SDL_Delay(5000);

	// Free resources and exit
	exit_code = 0;
l_exit:
	SDL_DestroyWindow(win);
	SDL_Quit();
	return exit_code;
}
