/*
 * sound.c
 *
 * handles game sounds
 */

#include <SDL2/SDL_mixer.h>

#include "dir.h"			// For DIR_SND
#include "error.h"
#include "sound.h"

// Loads a sound & handles errors
// Should only be used in snd_load_all()
#define	SND_LOAD(name)	snd_##name = snd_load_wav(DIR_SND #name ".wav"); \
						if (snd_##name == NULL) \
							goto l_error

// Sounds
Mix_Chunk *snd_point;
Mix_Chunk *snd_bounce;

// Loads a single sound, returns NULL on error
static Mix_Chunk *snd_load_wav(const char *path);

// Loads all game sounds, returns nonzero on error
int snd_load_all(void)
{
	// Load sounds
	SND_LOAD(point);
	SND_LOAD(bounce);

	return 0;

l_error:
	// Execution reaches here if any single sound fails to load
	snd_free_all();
	return 1;
}

// Frees all game sounds
void snd_free_all(void)
{
	Mix_FreeChunk(snd_point);
	Mix_FreeChunk(snd_bounce);
}

// Loads a single sound, returns NULL on error
static Mix_Chunk *snd_load_wav(const char *path)
{
	Mix_Chunk *chunk = Mix_LoadWAV(path);
	if (chunk == NULL)
	{
		PERR("Mix_LoadWav failed for file \"%s\". %s", path, Mix_GetError());
		return NULL;
	}
	return chunk;
}

// Plays a sound
void snd_play(Mix_Chunk *chunk)
{
	Mix_PlayChannel(-1, chunk, 0);
}
