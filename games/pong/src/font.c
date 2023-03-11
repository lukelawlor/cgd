/*
 * font.c
 *
 * contains sprite font rendering code
 */

#include <SDL2/SDL.h>

#include "font.h"
#include "sdl.h"
#include "texture.h"

// Number of rows and columns of character sprites in the font spritesheet
#define	FONT_SPR_ROWS		16
#define	FONT_SPR_COLS		8

// Draws sprite font text
void font_draw_text(const char *str, int x, int y)
{
	SDL_Rect srect = {
		.w = FONT_CHAR_WIDTH,
		.h = FONT_CHAR_HEIGHT,
	};
	SDL_Rect drect = {
		x,
		y,
		FONT_CHAR_WIDTH,
		FONT_CHAR_HEIGHT,
	};
	// Pointer used to traverse through the string
	char *ptr = (char *) str;

	// The current character being read from the string
	char c;
	while (*ptr != '\0')
	{
		c = *ptr;
		switch (c)
		{
		case ' ':
			// Skip over spaces
			drect.x += FONT_CHAR_XSPACE;
			break;
		case '\n':
			// Move 1 line down for newlines
			drect.x = x;
			drect.y += FONT_CHAR_YSPACE;
			break;
		default:
			// Draw a character normally
			srect.x = (c % FONT_SPR_ROWS) * FONT_CHAR_WIDTH;
			srect.y = (c / FONT_SPR_ROWS) * FONT_CHAR_HEIGHT;
			drect.x += FONT_CHAR_XSPACE;
			SDL_RenderCopy(g_ren, tex_font, &srect, &drect);
		}
		ptr++;
	}
}
