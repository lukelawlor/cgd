/*
 * mixer.c
 *
 * This program plays sound effects and music.
 *
 * Pressing 1 will play a c64 appregiated square wave sound effect
 * Pressing 2 will play a c64 snare drum sound effect
 * Pressing 3 will play background music
 * Pressing 4 will pause/resume the music
 */

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "error.h"

// Loads a Mix_Chunk object from path, returns NULL on error
Mix_Chunk *load_chunk(const char *path);

int main(int argc, char **argv)
{
	int exit_code = 1;

	// The window
	SDL_Window *win = NULL;

	// The sound effects
	Mix_Chunk *snd_square = NULL;
	Mix_Chunk *snd_snare = NULL;

	// The music
	Mix_Music *music = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		PERR("SDL_Init failed. %s", SDL_GetError());
		goto l_exit;
	}

	// Create the window
	const char *win_name = "mixer";
	const int win_width = 100;
	const int win_height = 100;
	win = SDL_CreateWindow(
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

	// Open the audio device
	// NOTE: There is a function called Mix_Init() that can be used to initialize various music libraries, but we won't be calling it here since we're only playing sound effects
	if (Mix_OpenAudio(
		// Audio frequency in hertz
		44100,

		// Audio format
		MIX_DEFAULT_FORMAT,

		// Number of channels
		2, 

		// Chunk size
		// You generally don't need to change this, see https://wiki.libsdl.org/SDL_mixer/Mix_OpenAudio for more details
		2048

		) < 0)
	{
		PERR("Mix_OpenAudio failed. %s", Mix_GetError());
		goto l_exit;
	}

	// Sound effects
	snd_square = load_chunk("square.wav");
	if (snd_square == NULL)
		goto l_exit;
	snd_snare = load_chunk("snare.wav");
	if (snd_square == NULL)
		goto l_exit;
	
	// Music
	music = Mix_LoadMUS("egg.mp3");
	if (music == NULL)
	{
		PERR("Mix_LoadMUS failed. %s", Mix_GetError());
		goto l_exit;
	}

	// Handle SDL events in a loop
	SDL_Event e;
	bool game_running = true;
	printf("Focus the window to detect keyboard input\n");
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
				case SDL_SCANCODE_1:
					Mix_PlayChannel(-1, snd_square, 0);
					break;
				case SDL_SCANCODE_2:
					Mix_PlayChannel(-1, snd_snare, 0);
					break;
				case SDL_SCANCODE_3:
					Mix_PlayMusic(music, -1);
					break;
				case SDL_SCANCODE_4:
					if (Mix_PausedMusic())
						Mix_ResumeMusic();
					else
						Mix_PauseMusic();
					break;
				}
				break;
			}
		}

		// Delay the program by 16 milliseconds so the loop is run at roughly 60fps
		// This is not the best method of timing since it doesn't take monitor refresh rates into account, but for these test programs it's fine
		SDL_Delay(16);
	}

	// Free resources and exit
	exit_code = 0;
l_exit:
	Mix_FreeMusic(music);
	Mix_FreeChunk(snd_square);
	Mix_FreeChunk(snd_snare);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_DestroyWindow(win);
	SDL_Quit();
	return exit_code;
}

// Loads a Mix_Chunk object from path, returns NULL on error
Mix_Chunk *load_chunk(const char *path)
{
	Mix_Chunk *chunk = Mix_LoadWAV(path);
	if (chunk == NULL)
	{
		PERR("Failed to load %s. %s", path, Mix_GetError());
		return NULL;
	}
	return chunk;
}
