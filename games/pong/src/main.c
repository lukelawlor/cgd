#include <stdio.h>

#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
	int exit_code = 1;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "SDL_Init failed. %s\n", SDL_GetError());
		goto l_exit;
	}

	printf("SDL initted yay\n");

	exit_code = 0;
l_exit:
	return exit_code;
}
