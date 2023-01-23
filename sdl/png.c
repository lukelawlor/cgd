/*
 * png.c
 *
 * This program loads and renders a PNG image.
 *
 * To compile this program, append "-lSDL2_image" to your compile command from init.c
 */

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "error.h"

int main(int argc, char **argv)
{
	int exit_code = 1;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		PERR("SDL_Init failed. %s", SDL_GetError());
		goto l_exit;
	}

	// Initialize SDL_image and enable PNG loading
	const int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags))
	{
		PERR("IMG_Init failed. %s", IMG_GetError());
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

	// Create the renderer
	const int ren_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, ren_flags);
	if (ren == NULL)
	{
		PERR("SDL_CreateRenderer failed. %s\n", SDL_GetError());
		goto l_exit;
	}

	// Create a surface
	// This is the general image storage format used by SDL
	// Here we are loading a PNG into it
	SDL_Surface *surf = IMG_Load("dude.png");

	// Load a PNG into surf
	if (surf == NULL)
	{
		PERR("IMG_Load failed. %s", IMG_GetError());
		goto l_exit;
	}

	// Create a texture
	// SDL's renderer can only render textures, so we will convert our surface into a texture to display it on our window
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
	if (tex == NULL)
	{
		PERR("SDL_CreateTextureFromSurface failed. %s", SDL_GetError());
		goto l_exit;
	}
	
	// Now that the surface has been converted to a texture, we no longer need it
	SDL_FreeSurface(surf);

	// We're setting surf to NULL here so when SDL_FreeSurface() is called again later there's no error
	// Attempting to free the same piece of memory twice will cause an error in SDL_FreeSurface() just as it does with free()
	surf = NULL;

	// Handle SDL events in a loop
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

		// See render_clear.c for explanation of this
		SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);

		// Clear the screen with the renderer draw color (black atm)
		SDL_RenderClear(ren);

		// Source rectangle
		// This is a pointer to a rectangle that selects which part of the texture to draw
		// If NULL, the entire texture is selected
		SDL_Rect *srect = NULL;

		// Destination rectangle
		// This is a pointer to a rectangle that selects which part of the screen to draw the texture to
		// If NULL, the entire screen is selected
		SDL_Rect *drect = NULL;

		// Render the entire texture across the entire screen
		SDL_RenderCopy(ren, tex, srect, drect);

		// Update the screen to reflect the renderer's changes to it
		SDL_RenderPresent(ren);
	}

	// Free resources and exit
	exit_code = 0;
l_exit:
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	IMG_Quit();
	SDL_Quit();
	return exit_code;
}
