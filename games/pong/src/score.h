/*
 * score.h
 *
 * scoreboard type & functions
 */

#ifndef	SCORE_H
#define	SCORE_H

typedef struct{
	int pts_left;
	int pts_right;
} Score;

extern Score g_score;

// Draws the scoreboard
void score_draw(void);

#endif
