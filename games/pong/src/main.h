/*
 * main.h
 *
 * miscellaneous macros
 */

#ifndef	MAIN_H
#define	MAIN_H

// Window dimensions
#define	WIN_WIDTH	800
#define	WIN_HEIGHT	800

// Border around the game world
#define	ARENA_BORDER	40

// SDL objects
extern SDL_Window *g_win;
extern SDL_Renderer *g_ren;

// SDL key state
extern const Uint8 *g_key_state;

#endif
