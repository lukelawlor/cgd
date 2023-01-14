/*
 * rectangles.c
 *
 * This program creates a window and renders rectangles on it
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

	// Create a window
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

	// Create a renderer
	SDL_Renderer *ren;
	const int ren_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	if ((ren = SDL_CreateRenderer(win, -1, ren_flags)) == NULL)
	{
		PERR("SDL_CreateRenderer failed. %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
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

		// See render_clear.c for explanation of this
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

		// Clear the screen with the renderer draw color (black atm)
		SDL_RenderClear(ren);
		
		SDL_Rect rect1 = {40, 20, 60, 80};
		SDL_Rect rect2 = {230, 200, 40, 80};
		SDL_Rect rect3 = {220, 60, 90, 30};

		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderDrawRect(ren, &rect1);

		SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		SDL_RenderDrawRect(ren, &rect2);

		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		SDL_RenderDrawRect(ren, &rect3);

		rect3.x += 50;
		rect3.y += 50;
		SDL_RenderFillRect(ren, &rect3);

		// Update the screen to reflect the renderer's changes to it
		SDL_RenderPresent(ren);
	}

	// Free resources and exit
l_exit:
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
