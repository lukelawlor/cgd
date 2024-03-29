/*
 * texture.h
 *
 * handles game textures
 */

#include <SDL2/SDL.h>		// For SDL_Texture
#include <SDL2/SDL_image.h>	// For IMG_Load

#include "dir.h"			// For DIR_RES
#include "error.h"
#include "sdl.h"			// For g_ren
#include "texture.h"

// Loads a texture & handles errors
// Should only be used in tex_load_all()
#define	TEX_LOAD(name)	tex_##name = tex_load_png(DIR_TEX #name ".png"); \
						if (tex_##name == NULL) \
							goto l_error

// Textures
SDL_Texture *tex_font;
SDL_Texture *tex_ball;

// Loads a single texture, returns NULL on error
static SDL_Texture *tex_load_png(const char *path);

// Loads all game textures, returns nonzero on error
int tex_load_all(void)
{
	// Load textures
	TEX_LOAD(font);
	TEX_LOAD(ball);

	// Change font color
	if (SDL_SetTextureColorMod(tex_font, 128, 180, 33) == -1)
		PERR("texture color mod did not work for the font. NOT SICK GUYS.");
	return 0;

l_error:
	// Execution reaches here if any single texture fails to load
	tex_free_all();
	return 1;
}

// Frees all game textures
void tex_free_all(void)
{
	SDL_DestroyTexture(tex_font);
	SDL_DestroyTexture(tex_ball);
}

// Loads a single texture, returns NULL on error
static SDL_Texture *tex_load_png(const char *path)
{
	SDL_Surface *surf;
	SDL_Texture *tex;

	// Load the image into the surface
	surf = IMG_Load(path);
	if (surf == NULL)
	{
		PERR("IMG_Load failed for file \"%s\". %s", path, IMG_GetError());
		return NULL;
	}

	// Create a texture from the surface
	tex = SDL_CreateTextureFromSurface(g_ren, surf);
	if (tex == NULL)
	{
		PERR("SDL_CreateTextureFromSurface failed for file \"%s\". %s", path, IMG_GetError());
		return NULL;
	}

	// Free the surface now that we don't need it
	SDL_FreeSurface(surf);

	return tex;
}
