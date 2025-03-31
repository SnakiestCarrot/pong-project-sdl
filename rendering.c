
#include "rendering.h"
#include "constants.h"
#include "structs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Window *window;
SDL_Surface *surface;
SDL_Renderer *renderer;

void window_init(char *window_name)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(renderer);
}

/*
Helper function to handle drawing rectangles with SDL
*/
void draw_rectangle(int xpos, int ypos, int width, int height)
{
	SDL_Rect rectangle = {xpos, ypos, width, height};
	SDL_RenderFillRect(renderer, &rectangle);
}

void display_clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void display_update()
{
	SDL_RenderPresent(renderer);
	SDL_Delay(1000 / FPS);
	display_clear();
}

void display_string(int line, char *text)
{
	// Taken from https://stackoverflow.com/a/22889483 
	TTF_Font *Sans = TTF_OpenFont("Sans.ttf", 7*SCREEN_SCALING);

	SDL_Color White = {255, 255, 255};

	SDL_Surface *surfaceMessage =
		TTF_RenderText_Solid(Sans, text, White);

	SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect;
	SDL_GetClipRect(surfaceMessage, &Message_rect);
	Message_rect.x = 0;
	Message_rect.y = line*(SCREEN_HEIGHT/4);

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void display_4_strings ( char *line0, char *line1, char *line2, char *line3 ) {
  display_string(0, line0);
  display_string(1, line1);
  display_string(2, line2);
  display_string(3, line3);
  display_update();
}

void display_buffer(char *buffer[])
{
    display_4_strings(buffer[0], buffer[1], buffer[2], buffer[3]);
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
