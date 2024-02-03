// This program demonstrates the use of the static keyword on local variables
// For use of static on functions and global variables, see ./compilation.org

#include <stdio.h>

// Print out information about the static variable x
void print_x(void);

// Print out information about the static variable x
void print_x(void)
{
	// x is a static local variable
	// When the static keyword is used on a local variable, the lifetime of the variable is changed
	// The variable is created in memory when the declaration or initialization statement of it is first reached
	// The variable will then exist in memory until the program ends
	// When the declaration or initialization statement is reached after the first time, it is ignored
	// The value of the static variable will remain the same as it was when the function its in was last called
	// Some people prefix static variable names with s_, similar to how global variables can be prefixed with g_
	// If you declare a static variable, it is initialized with the value 0, just like global variables
	static int x = 0;
	int y = 0;

	++x;
	++y;
	printf("x is %d, y is %d\n", x, y);
}

int main(void)
{
	// Can you guess what the following three function calls will print out?
	// Read the next group of comments for the answer
	print_x();
	print_x();
	print_x();
	
	// Since x is static, it will retain its value across multiple function calls
	// Each time print_x() is called, the value of x will increase
	// y is not static, so it will be re-created upon every function call and have a value of 1 at the time of printing
	return 0;
}
