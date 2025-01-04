
#include "rendering.h"
#include "constants.h"
#include "structs.h"
#include <SDL2/SDL.h>

SDL_Window *window;
SDL_Surface *surface;

void window_init(char *window_name)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
}

/*
Helper function to handle drawing rectangles with SDL
*/
void draw_rectangle(int xpos, int ypos, int width, int height)
{
	SDL_Rect rectangle = {xpos, ypos, width, height};
	SDL_FillRect(surface, &rectangle, COLOR_WHITE);
}

void display_clear()
{
	SDL_FillRect(surface, NULL, COLOR_BLACK);
}

void display_update()
{
	SDL_UpdateWindowSurface(window);
	SDL_Delay(1000 / FPS);
	display_clear();
}

void display_pixel(int xPos, int yPos)
{
	draw_rectangle(xPos * SCREEN_SCALING, yPos * SCREEN_SCALING, SCREEN_SCALING, SCREEN_SCALING);
}

void display_ball(struct Ball *ball)
{
	int x = ball->posX;
	int y = ball->posY;

	int i, j;
	int ballX = (int)x; // casting solves visual bug
	int ballY = (int)y; // casting solves visual bug
	for (i = 0; i < BALLSIZE; i++)
	{
		for (j = 0; j < BALLSIZE; j++)
		{
			display_pixel(ballX + j, ballY + i);
		}
	}
}

void display_paddle(struct Paddle *paddle)
{
	double x = paddle->posX;
	double y = paddle->posY;
	
	// typecasting here solves a rare bug
	int paddleX = (int)x;
	int paddleY = (int)y;

	int i = 0;
	for (i = 0; i < PADDLESIZE; i++)
	{
		display_pixel(paddleX, paddleY + i);
	}
}
