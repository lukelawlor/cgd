/*
 * init.h
 *
 * contains game initialization code
 */

#ifndef	INIT_H
#define	INIT_H

// Initializes everything needed to start the game loop, returns nonzero on error
int game_init(void);

// Undoes initialization steps done by game_init()
void game_quit(void);

#endif
