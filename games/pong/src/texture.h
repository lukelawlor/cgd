/*
 * texture.h
 *
 * handles game textures
 */

#ifndef	TEXTURE_H
#define	TEXTURE_H

#include <SDL2/SDL.h>	// For SDL_Texture

// Textures
extern SDL_Texture *tex_font;
extern SDL_Texture *tex_ball;

// Loads all game textures, returns nonzero on error
int tex_load_all(void);

// Frees all game textures
void tex_free_all(void);

#endif
