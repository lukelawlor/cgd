/*
 * event.c
 *
 * This program creates a new window and exits when an SDL_QUIT event is triggered. This happens when the user presses X to close the window.
 */

#include <stdio.h>
#include <stdbool.h>

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

	// Handle SDL events
	SDL_Event e;
	while (true)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				goto l_exit;
			}
		}
	}

	// Free resources and exit
l_exit:
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
