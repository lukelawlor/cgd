/*
 * error.h
 *
 * functions for printing error messages
 */

#ifndef	ERROR_H
#define	ERROR_H

#include <stdio.h>

// Print start of error message
void perr_start(void);

// Print end of error message
void perr_end(void);

#define	PERR(...)	perr_start();\
			fprintf(stderr, __VA_ARGS__);\
			perr_end()

#endif
