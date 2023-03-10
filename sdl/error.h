/*
 * error.h
 *
 * This file contains a macro for printing errors called PERR().
 *
 * You can call it with the same parameters as printf().
 */

#ifndef	ERROR_H
#define	ERROR_H

// Start and end messages for every error
#define	PERR_START	"error: "
#define	PERR_END	"\n"

#ifdef	PERR_DISABLE
	#define	PERR(...)	{\
					fprintf(stderr, PERR_START);\
					fprintf(stderr, __VA_ARGS__);\
					fprintf(stderr, PERR_END);\
				}
#else
	#define	PERR(...)	do{}while(0)
#endif

#endif
