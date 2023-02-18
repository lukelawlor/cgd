/*
 * sdl.h
 *
 * contains SDL objects
 */

#ifndef	GAME_SDL_H
#define	GAME_SDL_H

#include <SDL2/SDL.h>

// Window dimensions
#define	WIN_WIDTH	800
#define	WIN_HEIGHT	800

// Renderer creation flags
#define	REN_FLAGS	(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)

// SDL objects
extern SDL_Window *g_win;
extern SDL_Renderer *g_ren;

// SDL key state
extern const Uint8 *g_key_state;

#endif
