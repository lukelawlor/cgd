/*
 * error.c
 *
 * functions for printing error messages
 */

#include <stdio.h>

#include "error.h"

// Print start of error message
void perr_start(void)
{
	fprintf(stderr, "pong: error: ");
}

// Print end of error message
void perr_end(void)
{
	fputc('\n', stderr);
}
