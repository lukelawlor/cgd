/*
 * sound.h
 *
 * handles game sounds
 */

#ifndef	SOUND_H
#define	SOUND_H

#include <SDL2/SDL_mixer.h>

// Sounds
extern Mix_Chunk *snd_point;
extern Mix_Chunk *snd_bounce;

// Loads all game sounds, returns nonzero on error
int snd_load_all(void);

// Frees all game sounds
void snd_free_all(void);

// Plays a sound
void snd_play(Mix_Chunk *chunk);

#endif
