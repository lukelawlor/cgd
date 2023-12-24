#include <stdio.h>

// Inline functions are functions whose definitions can be copied and pasted into the areas of code where they are called to avoid a function call in machine code
// Avoiding function calls can speed up your code, however, because the definitions of inline functions are copied and pasted wherever they are used, this may increase your executable's size

// The easiest way to create an inline function is to make it static and use the inline keyword
static inline void func(int x)
{	
	printf("x + 2 is %d\n", x + 2);
}

// The inline keyword is only a hint to the compiler
// The compiler may inline the function or not, depending on whether it thinks it will ultimately optimize your program

int main(void)
{
	func(5);
	return 0;
}

// To see a demo of non-static inline functions being used, see the non-static-inline/ directory
// I myself don't completely understand non-static inline functions yet. For more info on them, see here: https://en.cppreference.com/w/c/language/inline 
