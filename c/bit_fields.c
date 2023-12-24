#include <stdio.h>
#include <stdbool.h>

// Bit fields are member variables of structs that take up only a set number of bits of memory
// You can use them to minimize memory usage
// For example, you might want to store booleans as bit fields that only take up 1 bit, since that's all the memory that is needed to store true or false

struct test{
	// ": 1" means that x will only take up 1 bit
	// Therefore, only the binary values 0 or 1 (false and true, respectively) can be stored in x
	bool x : 1;

	// You can create a bit field with no name like this
	// This will create empty space in the struct
	// You can use this to explicitly control the spacing of bit fields in your struct
	int : 4;

	// So far we have used 5 bits, so this 3 bit variable will make our struct 8 bits which should be 1 byte
	int y : 3;
};

// You cannot take the address of a bit field because pointers only point to bytes, not individual bits

int main(void)
{
	// A struct containing bit fields will still only take up a whole number of bytes
	
	// This will print a whole number
	printf("The size of test is: %ld\n", sizeof(struct test));
}
