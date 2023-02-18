/*
 * sdl.c
 *
 * contains SDL objects
 */

#include <SDL2/SDL.h>

#include "sdl.h"

// SDL objects
SDL_Window *g_win = NULL;
SDL_Renderer *g_ren = NULL;

// Get the keyboard state
const Uint8 *g_key_state = NULL;
