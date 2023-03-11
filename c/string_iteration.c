#include <stdio.h>

int main(void)
{
#if 0
	char str[6] = {
		'h',
		'e',
		'l',
		'l',
		'o',
		'\0',
	};
#endif

	char str[] = "hello";

	char *ptr = &str[0];

	while (*ptr != '\0')
	{
		putchar(*ptr);
		ptr++;
	}
	putchar('\n');

	return 0;
}
