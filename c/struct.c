#include <stdio.h>

// A struct is an example of a compound data type

// Structs can be used to store multiple variables inside a single variable

// This is a struct definition
// Here we are defining a type of struct with the struct tag Rectangle
// A struct tag is an identifier for a struct type
struct rectangle{
	// Inside the curly braces following the struct tag, we can declare variables
	// These variables will be stored inside our struct type
	// They are called "member variables"
	int x;
	int y;
	int width;
	int height;

	// The order in which the member variables are declared matters
};

// It is generally preferred to use a pointer to a struct as a parameter rather than a raw struct as a parameter
// I will explain why later
void print_rect_center(struct rectangle *r);

int main(void)
{
	// Here is how to create an object with a struct type we defined
	// This will declare a variable named rect with the type struct rectangle
	struct rectangle rect;

	// To access the variables inside rect, we can use the . operator like so
	rect.x = 0;
	rect.y = 5;
	rect.width = 10;
	rect.height = 10;

	// To initialize a struct, we can assign it to a list of variable initializers enclosed in curly braces
	// This will initialize our member variable x with 10, y with 20, width with 50, and height with 60
	// This is why the order that the member variables are declared matters
	// The first value specified in the initializer is assigned to the first member variable declared in the struct definition
	struct rectangle rect2 = {
		10,
		20,
		50,
		60,
	};
	// The comma after the final initializer can be left out
	// I personally like to leave it if I list the initializers vertically

	printf("rect2 is located at (%d, %d) and its dimensions are %dx%d\n", rect2.x, rect2.y, rect2.width, rect2.height);
	print_rect_center(&rect2);

	// If you don't like having to type struct + a struct tag to reference a struct type, use a typedef
	// This will define the type "Rectangle" as "struct rectangle"
	typedef struct rectangle Rectangle;

	// Now we can declare our struct objects like this
	Rectangle rect3;

	// You can also create a typedef around the definition of a struct like so
	typedef struct point{
		int x;
		int y;
	} Point;
	// Now we have defined the type "Point" as "struct point" while also defining the type "struct point" itself
	
	// You can also leave out the struct tag if using a typedef like this
	// A struct without a tag, like this one, is called an anonymous struct
	typedef struct{
		char *name;
		int age;
	} Person;

	// We can still access the struct type by using the Person type
	Person p = {"Luke", 17};

	// If you don't use a typedef, you can declare or initialize variables in the same line as a struct definition by listing variable names after the curly braces
	
	// This statement will define an anonymous struct and create an variable of its type named dog
	struct{
		char *name;
		int foods;
	} dog = {"Jim", 9999};

	// This statement will define a struct with the tag alien and create variables of its type named alien_a, alien_b, and alien_c
	struct alien{
		char *planet_name;
		char *name;
		int hp;
	} alien_a, alien_b, alien_c;
  
	return 0;
}

// Here is an example function showing the use of a struct pointer parameter
// It is generally preferred to use struct pointers as parameters instead of raw structs because, since arguments are copied into parameter when functions are called, copying a large struct object can be costly
// A struct pointer object will have the same size as any pointer, regardless of the size of the struct it points to, so passing struct pointers will be faster than passing a raw struct if your struct is larger than the size of a pointer
void print_rect_center(struct rectangle *r)
{
	// This function will print out the center of the rectangle
	
	// To access the a struct's variables from a pointer, we can use this syntax: (*pointer).member_variable
	// Or we can use the arrow operator: pointer->member_variable
	double center_x = r->x + (double) r->width / 2;
	double center_y = r->y + (double) r->height / 2;
	
	printf("The center of the rectangle is (%lf, %lf)\n", center_x, center_y);
}
