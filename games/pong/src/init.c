/*
 * init.c
 *
 * contains game initialization code
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "error.h"
#include "game.h"
#include "init.h"
#include "paddle.h"
#include "score.h"
#include "sdl.h"
#include "sound.h"
#include "texture.h"
#include "timestep.h"

// Initializes everything needed to start the game loop, returns nonzero on error
int game_init(void)
{
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		PERR("SDL_Init failed. %s", SDL_GetError());
		goto l_error;
	}

	// Create the window
	g_win = SDL_CreateWindow(
		"pong sick",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if (g_win == NULL)
	{
		PERR("SDL_CreateWindow like failed or stuff. %s", SDL_GetError());
		goto l_error;
	}

	// Set timestep
	SDL_DisplayMode dm;
	int di = SDL_GetWindowDisplayIndex(g_win);

	// Monitor refresh rate
	int refresh_rate;

	if (SDL_GetCurrentDisplayMode(di, &dm) == 0)
	{
		if (dm.refresh_rate != 0)
		{
			// Got refresh rate
			refresh_rate = dm.refresh_rate;
		}
		else
		{
			// Couldn't get refresh rate
			refresh_rate = 60;
		}
	}
	refresh_rate = 60;
	g_ts = refresh_rate / 60.0;

	// Create the renderer
	g_ren = SDL_CreateRenderer(
		g_win,
		-1,
		REN_FLAGS
	);
	if (g_ren == NULL)
	{
		PERR("SDL_CreateRenderer failed. %s", SDL_GetError());
		goto l_error;
	}

	// Initialize SDL_image
	if (!(IMG_Init(IMG_FLAGS) & IMG_FLAGS))
	{
		PERR("IMG_Init failed. %s", IMG_GetError());
		goto l_error;
	}

	// Initialize SDL_mixer
	if (!(Mix_Init(MIX_FLAGS) & MIX_FLAGS))
	{
		PERR("Mix_Init failed. %s", Mix_GetError());
		goto l_error;
	}

	// Open audio channels
	if (Mix_OpenAudio(MIX_RATE, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		PERR("Mix_OpenAudio failed. %s", Mix_GetError());
		goto l_error;
	}
	
	// Get keyboard state
	g_key_state = SDL_GetKeyboardState(NULL);

	// Initialize game objects
	g_left_paddle = (Paddle) {
		.x = ARENA_BORDER,
		.y = ARENA_BORDER,
		.key_up = SDL_SCANCODE_W,
		.key_down = SDL_SCANCODE_S,
	};
	g_right_paddle = (Paddle) {
		.x = WIN_WIDTH - ARENA_BORDER - PADDLE_WIDTH,
		.y = ARENA_BORDER,
		.key_up = SDL_SCANCODE_UP,
		.key_down = SDL_SCANCODE_DOWN,
	};
	g_score = (Score) {0, 0};

	if (tex_load_all())
		goto l_error;
	if (snd_load_all())
		goto l_error;

	// Success
	return 0;
l_error:
	game_quit();
	return 1;
}

// Undoes initialization steps done by game_init()
void game_quit(void)
{
	snd_free_all();
	tex_free_all();
	SDL_DestroyWindow(g_win);
	SDL_DestroyRenderer(g_ren);
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
