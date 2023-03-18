/*
 * math.c
 *
 * miscellaneous math functions
 */

#include "math.h"

// Clamp for ints
int clamp(int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

// Clamp for doubles
double clampf(double value, double min, double max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

// Returns -1 for negative numbers, 1 for positive numbers, and 0 for 0
// Used for ints
int sign(int value)
{
	return value > 0 ? 1 : (value < 0 ? -1 : 0);
}

// Returns -1 for negative numbers, 1 for positive numbers, and 0 for 0
// Used for doubles
int signf(double value)
{
	return value > 0 ? 1 : (value < 0 ? -1 : 0);
}
