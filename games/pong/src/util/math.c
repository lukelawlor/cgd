/*
 * math.c
 *
 * miscellaneous math functions
 */

#include "math.h"

double clamp(double value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}
