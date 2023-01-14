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
		return 1;
	}

	// Initialize SDL_image and enable PNG loading
	const int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags))
	{
		PERR("IMG_Init failed. %s", IMG_GetError());
		SDL_Quit();
		return 1;
	}

	// Create a window
	SDL_Window *win = NULL;
	const char *win_name = "good window";
	const int win_width = 640;
	const int win_height = 480;

	if ((win = SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) == NULL)
	{
		PERR("SDL_CreateWindow failed. %s", SDL_GetError());
		goto l_exit;
	}

	// Create a renderer
	SDL_Renderer *ren = NULL;
	const int ren_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	if ((ren = SDL_CreateRenderer(win, -1, ren_flags)) == NULL)
	{
		PERR("SDL_CreateRenderer failed. %s", SDL_GetError());
		goto l_exit;
	}

	// Create a surface
	// This is the image storage format used by SDL
	// We will load a PNG into it and then convert it to a texture to be used by our graphics card
	SDL_Surface *surf = NULL;

	// Create a texture
	SDL_Texture *tex = NULL;

	// Load a PNG into surf
	if ((surf = IMG_Load("dude.png")) == NULL)
	{
		PERR("IMG_Load failed. %s", IMG_GetError());
		goto l_exit;
	}

	// Conver the surface to a texture
	if ((tex = SDL_CreateTextureFromSurface(ren, surf)) == NULL)
	{
		PERR("SDL_CreateTextureFromSurface failed. %s", SDL_GetError());
		goto l_exit;
	}
	
	// Now that the surface has been converted to a texture, we no longer need it
	SDL_FreeSurface(surf);
	surf = NULL;

	// Handle SDL events
	SDL_Event e;
	while (true)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				goto l_end;
			}
		}

		// See render_clear.c for explanation of this
		SDL_SetRenderDrawColor(ren, 0, 60, 180, 255);

		// Clear the screen with the renderer draw color (black atm)
		SDL_RenderClear(ren);

		// Source rectangle
		// This is a rectangle that selects which part of the texture to draw
		SDL_Rect *srect = NULL;

		// Destination rectangle
		// This is a rectangle that selects which part of the screen to draw the texture to
		SDL_Rect *drect = NULL;

		SDL_RenderCopy(ren, tex, srect, drect);
		
		// Update the screen to reflect the renderer's changes to it
		SDL_RenderPresent(ren);
	}

	// Render loop end
l_end:
	exit_code = 0;

	// Free resources and exit
l_exit:
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	IMG_Quit();
	SDL_Quit();
	return exit_code;
}
