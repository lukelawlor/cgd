#include <stdio.h>
#include <stdint.h>

// unsigned integer with 8 bits
// can hold positive values ONLY
typedef uint8_t u8;

// signed integer with 8 bits
// can hold positive AND negative values
typedef int8_t i8;

int main(void)
{
	u8 x;
	// x = 00000000
	// each 0 or 1 is a bit
	// every 8 bits is 1 byte (on most machines, it might vary on different hardware)
	// every 4 bits is 1 nybble
	// the left-most bit is the most significant bit (MSB) which has the largest effect on the value of the number
	// the right-most bit is the least significant bit (LSB) which has the least effect on the value of the number
	// on some machines, the places of the LSB and MSB are swapped
	x = 0;

	// x = 10000001
	x = 1;

	// x = 00000010
	x = 2;

	// x = 00000011
	x = 3;

        // carry space  11
	// x =     00000011
	// adding  00000001
	// equals  00000100
	// now x = 00000100
	x = 3;

	// signed and unsigned integers hold the same amount of bits
	// but they use them differently
	
	i8 y;
	// y = 00000000
	// The MSB of a signed integer is called the "sign bit"
	// Usually, if the sign bit is 0, the number is positive, otherwise, the number is negative
	y = -5;

	printf("sign bit of y: %d\n", y >>= 7);
	return 0;
}
