/*
 * keyboard.c
 *
 * This program prints key presses to stdout.
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
	const char *win_name = "keyboard";
	const int win_width = 100;
	const int win_height = 100;
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

	// Get the keyboard state
	Uint8 *key_state = SDL_GetKeyboardState(NULL);
	
	// Handle SDL events in a loop
	SDL_Event e;
	bool game_running = true;
	printf("Focus the window to detect keyboard input\n");
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
				// Method #1 for getting keyboard input:
				// Checking for SDL_KEYDOWN or SDL_KEYUP events
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
					printf("You pressed W\n");
					break;
				case SDL_SCANCODE_A:
					printf("You pressed A\n");
					break;
				case SDL_SCANCODE_S:
					printf("You pressed S\n");
					break;
				case SDL_SCANCODE_D:
					printf("You pressed D\n");
					break;
				case SDL_SCANCODE_Q:
					game_running = false;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
					printf("You released W\n");
					break;
				case SDL_SCANCODE_A:
					printf("You released A\n");
					break;
				case SDL_SCANCODE_S:
					printf("You released S\n");
					break;
				case SDL_SCANCODE_D:
					printf("You released D\n");
					break;
				}
				break;
			}
		}

		// Method #2 for getting keyboard input:
		// Accessing the keyboard state array

		// This has slightly nicer syntax, but only tells you when keys are being held, not pressed or released
		if (key_state[SDL_SCANCODE_H])
			printf("H is being held\n");
		if (key_state[SDL_SCANCODE_J])
			printf("J is being held\n");
		if (key_state[SDL_SCANCODE_K])
			printf("K is being held\n");
		if (key_state[SDL_SCANCODE_L])
			printf("L is being held\n");
	}

	// Free resources and exit
	exit_code = 0;
l_exit:
	SDL_DestroyWindow(win);
	SDL_Quit();
	return exit_code;
}
