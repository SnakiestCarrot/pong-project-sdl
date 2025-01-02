
#include "constants.h"
#include "rendering.h"

/*
  Helper function to handle drawing rectangles with SDL
*/
void draw_rectangle(SDL_Surface *surface, int xpos, int ypos, int width, int height)
{
  SDL_Rect rectangle = {xpos, ypos, width, height};
  SDL_FillRect(surface, &rectangle, COLOR_WHITE);
}

void display_update(SDL_Window* window)
{
  SDL_UpdateWindowSurface(window);
}

void display_pixel(SDL_Surface* surface, int xPos, int yPos)
{
  draw_rectangle(surface, xPos*SCREEN_SCALING, yPos*SCREEN_SCALING, SCREEN_SCALING, SCREEN_SCALING);
}

void display_ball(SDL_Surface* surface, double x, double y)
{
  int i, j;
  int ballX = (int)x; // casting solves visual bug
  int ballY = (int)y; // casting solves visual bug
  for (i = 0; i < BALLSIZE; i++)
  {
    for (j = 0; j < BALLSIZE; j++)
    {
      display_pixel(surface, ballX + j, ballY + i);
    }
  }
}