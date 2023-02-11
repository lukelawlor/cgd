#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "error.h"

// Window dimensions
#define	WIN_WIDTH	800
#define	WIN_HEIGHT	800

#define	ARENA_BORDER	10

// Paddle settings
#define	PADDLE_SPEED	16

#define	PADDLE_WIDTH	12
#define	PADDLE_HEIGHT	40

#define	PADDLE_Y_MIN	ARENA_BORDER
#define	PADDLE_Y_MAX	(WIN_HEIGHT - ARENA_BORDER - PADDLE_HEIGHT)

// Keys
#define	KEY_PADDLE_LEFT_UP	SDL_SCANCODE_W
#define	KEY_PADDLE_LEFT_DOWN	SDL_SCANCODE_S
#define	KEY_PADDLE_RIGHT_UP	SDL_SCANCODE_UP
#define	KEY_PADDLE_RIGHT_DOWN	SDL_SCANCODE_DOWN

// Renderer flags
#define	REN_FLAGS	(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)

// SDL objects
SDL_Window *g_win = NULL;
SDL_Renderer *g_ren = NULL;

typedef struct Paddle{
	double x;
	double y;
} Paddle;

double clamp(double value, int min, int max);

void paddle_draw(Paddle *paddle)
{
	SDL_SetRenderDrawColor(g_ren, 0, 0, 0, 255);
	SDL_Rect drect = {
		(int) paddle->x,
		(int) paddle->y,
		PADDLE_WIDTH,
		PADDLE_HEIGHT,
	};
	SDL_RenderFillRect(g_ren, &drect);
}

int main(int argc, char **argv)
{
	int exit_code = 1;

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		PERR("SDL_Init failed. %s\n", SDL_GetError());
		goto l_exit;
	}

	// Create the window
	g_win = SDL_CreateWindow(
		"PONG",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if (g_win == NULL)
	{
		PERR("SDL_CreateWindow like failed or stuff. %s\n", SDL_GetError());
		goto l_exit;
	}

	// Create the renderer
	g_ren = SDL_CreateRenderer(
		g_win,
		-1,
		REN_FLAGS
	);
	if (g_ren == NULL)
	{
		PERR("SDL_CreateRenderer failed. %s\n", SDL_GetError());
		goto l_exit;
	}


	// Get the keyboard state
	const Uint8 *key_state = SDL_GetKeyboardState(NULL);

	Paddle left_paddle = {
		ARENA_BORDER,
		ARENA_BORDER,
	};
	Paddle right_paddle = {
		WIN_WIDTH - ARENA_BORDER - PADDLE_WIDTH,
		ARENA_BORDER,
	};

	// Game loop
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
			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_Q:
					game_running = false;
					break;
				default:
					break;
				}
			}
		}

		if (key_state[KEY_PADDLE_LEFT_UP])
			left_paddle.y -= PADDLE_SPEED;
		if (key_state[KEY_PADDLE_LEFT_DOWN])
			left_paddle.y += PADDLE_SPEED;
		if (key_state[KEY_PADDLE_RIGHT_UP])
			right_paddle.y -= PADDLE_SPEED;
		if (key_state[KEY_PADDLE_RIGHT_DOWN])
			right_paddle.y += PADDLE_SPEED;

		left_paddle.y = clamp(
			left_paddle.y,
			PADDLE_Y_MIN,
			PADDLE_Y_MAX
		);
		right_paddle.y = clamp(
			right_paddle.y,
			PADDLE_Y_MIN,
			PADDLE_Y_MAX
		);

		//if (key_state[KEY_PADDLE_RIGHT_UP])
		//	left_paddle.y += PADDLE_SPEED;
//
//		if (key_state[KEY_PADDLE_RIGHT_DOWN])
//			left_paddle.y -= PADDLE_SPEED;

		SDL_SetRenderDrawColor(g_ren, 255, 200, 100, 255);
		SDL_RenderClear(g_ren);

		paddle_draw(&left_paddle);
		paddle_draw(&right_paddle);

		SDL_RenderPresent(g_ren);
	}

	exit_code = 0;
l_exit:
	SDL_DestroyWindow(g_win);
	SDL_DestroyRenderer(g_ren);
	SDL_Quit();
	return exit_code;
}

double clamp(double value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}
