
#include <SDL2/SDL.h>
#include "constants.h"
#include "rendering.h"

SDL_Window* window;
SDL_Surface* surface;

void window_init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Blank Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
}

int main(int argc, char* argv[]) 
{
	window_init();

    display_ball(surface,3,3);

    display_update(window);

    SDL_Delay(3000);

	return 0;
}
