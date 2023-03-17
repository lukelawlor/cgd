/*
 * score.c
 *
 * scoreboard type & functions
 */

#include <stdio.h>	// For snprintf()

#include "font.h"
#include "score.h"
#include "sdl.h"	// For WIN_WIDTH & WIN_HEIGHT
#include "game.h"	// For ARENA_BORDER

// # of bytes dedicated to the string used to store scoreboard numbers in before they're drawn
#define	SCORE_STR_LEN	5

Score g_score;

// Draws the scoreboard
void score_draw(void)
{
	// String to hold scoreboard numbers in
	char score_str[SCORE_STR_LEN];
	snprintf(score_str, SCORE_STR_LEN, "%d", g_score.pts_left);
	font_draw_text(score_str, ARENA_BORDER, ARENA_BORDER);
	snprintf(score_str, SCORE_STR_LEN, "%d", g_score.pts_right);
	font_draw_text(score_str, WIN_WIDTH / 2, ARENA_BORDER);
}
