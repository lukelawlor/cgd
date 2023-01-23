/*
 * mouse.c
 *
 * This program prints mouse events to stdout.
 */

#include <stdio.h>
#include <stdbool.h>

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
	const char *win_name = "mouse";
	const int win_width = 200;
	const int win_height = 200;
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

	// Handle SDL events in a loop
	SDL_Event e;
	bool game_running = true;
	printf("Focus the window to detect mouse input\n");
	while (game_running)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				game_running = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					printf("Left mouse button pressed\n");
					break;
				case SDL_BUTTON_MIDDLE:
					printf("Middle mouse button pressed\n");
					break;
				case SDL_BUTTON_RIGHT:
					printf("Right mouse button pressed\n");
					break;
				}
				printf("Press coordinates: (%d, %d)\n\n", e.button.x, e.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					printf("Left mouse button released\n");
					break;
				case SDL_BUTTON_MIDDLE:
					printf("Middle mouse button released\n");
					break;
				case SDL_BUTTON_RIGHT:
					printf("Right mouse button released\n");
					break;
				}
				printf("Release coordinates: (%d, %d)\n\n", e.button.x, e.button.y);
				break;
			case SDL_MOUSEWHEEL:
				if (e.wheel.y > 0)
					printf("Scroll up\n");
				else if (e.wheel.y < 0)
					printf("Scroll down\n");
				if (e.wheel.x > 0)
					printf("Scroll right\n");
				else if (e.wheel.x < 0)
					printf("Scroll left\n");
				break;
			case SDL_MOUSEMOTION:
				printf("Mouse moved to (%d, %d)\n", e.motion.x, e.motion.y);
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
