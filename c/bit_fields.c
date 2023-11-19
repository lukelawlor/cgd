#include <stdio.h>
#include <stdint.h>

// signed integers can contain negative and positive values
// unsigned integers only contain positive values

typedef struct{
	// ": 1" means that x will only take up 1 bit.
	unsigned int x : 1;

	// y has 7 bits
	int y : 7;
} Test;

int main(void)
{
	Test t = {0, 0};
	++t.x;
	++t.x;
	printf("%d\n", t.x);
}
