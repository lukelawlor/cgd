/*
 * math.h
 *
 * miscellaneous math functions
 */

#ifndef	UTIL_MATH_H
#define	UTIL_MATH_H

// Clamp for ints
int clamp(int value, int min, int max);

// Clamp for doubles
double clampf(double value, double min, double max);

// Returns -1 for negative numbers, 1 for positive numbers, and 0 for 0
// Used for ints
int sign(int value);

// Returns -1 for negative numbers, 1 for positive numbers, and 0 for 0
// Used for doubles
int signf(double value);

#endif
