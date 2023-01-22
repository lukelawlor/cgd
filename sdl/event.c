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
	int exit_code = 1;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		PERR("SDL_Init failed. %s", SDL_GetError());
		goto l_exit;
	}
	
	// Create the window
	const char *win_name = "good window";
	const int win_width = 640;
	const int win_height = 480;
	SDL_Window *win = SDL_CreateWindow(
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

	// Handle SDL events in a loop
	SDL_Event e;
	bool game_running = true;
	while (game_running)
	{
		// SDL_PollEvent() will write event data to our event object
		// When all events have been processed, it returns 0
		while (SDL_PollEvent(&e) != 0)
		{
			// Check what type of event was activated
			switch (e.type)
			{
			case SDL_QUIT:
				// An SDL_QUIT event type indicates that something has signaled our program to quit
				// This happens when you click the X on the window to close it
				game_running = false;
				break;
			}
		}

		// Delay the program by 16 milliseconds so the loop is run at roughly 60fps
		// This is not the best method of timing since it doesn't take monitor refresh rates into account, but for these test programs it's fine
		SDL_Delay(16);
	}

	// Free resources and exit
	exit_code = 0;
l_exit:
	SDL_DestroyWindow(win);
	SDL_Quit();
	return exit_code;
}
