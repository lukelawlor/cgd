/*
 * init.c
 *
 * This program will initialize SDL.
 *
 * To compile on Windows:
 * 	cc init.c -I<path to sdl include> -L<path to sdl lib> -Wl,-subsystem,console -lmingw32 -lSDL2main -lSDL2
 *
 * To compile on Linux:
 * 	cc init.c -lSDL2
 */

#include <stdio.h>

#include <SDL2/SDL.h>

// main must have this exact function header for any SDL program
int main(int argc, char **argv)
{
	// SDL_Init() must be called before any other SDL functions are called
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		// When an SDL call falls, an error message can be retrieved with SDL_GetError()
		fprintf(stderr, "SDL_Init() failed. SDL Error: %s\n", SDL_GetError());
		return 1;
	}

	printf("SDL has successfully initialized!\n");

	SDL_Window *win;

	// SDL_Quit() must be called to shut SDL down
	SDL_Quit();
	return 0;
}
