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
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		PERR("SDL_Init failed. %s", SDL_GetError());
		return 1;
	}
	
	SDL_Window *win;
	const char *win_name = "good window";
	const int win_width = 640;
	const int win_height = 480;

	if ((win = SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) == NULL)
	{
		PERR("SDL_CreateWindow failed. %s", SDL_GetError());

		SDL_Quit();
		return 1;
	}

	// Wait for 5 seconds
	SDL_Delay(5000);

	// Free resources and exit
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
