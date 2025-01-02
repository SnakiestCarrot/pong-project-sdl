/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson
   Updated for Pong Project
   by Casper Johansson and August Wikdahl 2024
   except where specified.

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <math.h>
#include <SDL2/SDL.h>
#include "display.h"


#define SCREEN_SCALING 8

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32

#define SCREEN_WIDTH (DISPLAY_WIDTH * SCREEN_SCALING)
#define SCREEN_HEIGHT (DISPLAY_HEIGHT * SCREEN_SCALING)

#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000

SDL_Window *window;
SDL_Surface *surface;

void window_init()
{
  SDL_Init(SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow("Blank Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  surface = SDL_GetWindowSurface(window);
}

void display_update(void)
{
  SDL_UpdateWindowSurface(window);
}

/*
  Helper function to handle drawing rectangles with SDL
*/
void draw_rectangle(SDL_Surface *surface, int xpos, int ypos, int width, int height)
{
  SDL_Rect rectangle = {xpos, ypos, width, height};

  SDL_FillRect(surface, &rectangle, COLOR_WHITE);
}

// Change this to make ball larger, measured in pixels
int ballSize = 2;

void display_string(int line, char *s)
{
  
}

/* display4Strings:

  Takes 4 strings as input and writes them to the corresponding line
  on the display, then updates the display so the display actually shows the strings
  Made by Casper Johansson.
*/
void display4Strings(char *line0, char *line1, char *line2, char *line3)
{
  display_string(0, line0);
  display_string(1, line1);
  display_string(2, line2);
  display_string(3, line3);
  display_update();
}

// Takes x and y-coordinate for a pixel and adds it to the screen surface.
void displayPixel(int xPos, int yPos)
{
  draw_rectangle(surface, xPos*SCREEN_SCALING, yPos*SCREEN_SCALING, SCREEN_SCALING, SCREEN_SCALING);
  return;
}



/*
  Writes a rectangle ((ballSize)x(ballSize) pixels) with its upper left corner
  on the specified x and y coordinates into the display buffer

  Made by Casper Johansson
*/
void displayBall(double x, double y)
{
  int i, j;
  int ballX = (int)x; // casting solves visual bug
  int ballY = (int)y; // casting solves visual bug
  for (i = 0; i < ballSize; i++)
  {
    for (j = 0; j < ballSize; j++)
    {
      displayPixel(ballX + j, ballY + i);
    }
  }
}

/*
  Writes a paddle into the display buffer with its
  top-most pixel on the specified x and y coordinates
  into the display buffer

  Made by Casper Johansson
*/
void displayPaddle(double x, double y)
{
  // typecasting here solves a rare bug
  int paddleX = (int)x;
  int paddleY = (int)y;

  int i = 0;
  for (i = 0; i < 8; i++)
  {
    displayPixel(paddleX, paddleY + i);
  }
}

void displayClr(void)
{
  SDL_FillRect(surface, NULL, COLOR_BLACK);
}

/* void displayCredits(void)
{
  display4Strings("Made by;", "August Wikdahl", "Casper", "Johansson");
  quicksleep(30000000);
} */

// char scoreStr[] = "       -  ";

// Function to update the score-string from the integer scores.
// Made by August Wikdahl and Casper Johansson.
/* char *scoreToStr(int scoreLeft, int scoreRight)
{

  char firstLeft = (char)((scoreLeft / 10) + 48);
  char secondLeft = (char)((scoreLeft % 10) + 48);

  char firstRight = (char)((scoreRight / 10) + 48);
  char secondRight = (char)((scoreRight % 10) + 48);

  scoreStr[4] = firstLeft;
  scoreStr[5] = secondLeft;

  scoreStr[9] = firstRight;
  scoreStr[10] = secondRight;

  return scoreStr;
} */

// Displaying the score
/* void displayGameScore(int scoreLeft, int scoreRight)
{
  display4Strings("    L    R", scoreToStr(scoreLeft, scoreRight), "", "");
  quicksleep(10000000);
} */

// Displaying winner at the end of game
/* void displayWinnerScreen(int scoreLeft, int scoreRight)
{
  display_string(1, scoreToStr(scoreLeft, scoreRight));
  display_string(2, "");
  display_string(3, "");

  if (scoreLeft > scoreRight)
  {
    display_string(0, "   Left wins!");
  }

  else if (scoreLeft < scoreRight)
  {
    display_string(0, "  Right wins!");
  }

  else
  {
    display_string(0, " It's a draw!");
  }

  display_update();
  quicksleep(10000000);
} */

// Display countdown before match
// Made by Casper Johansson
/* 
void displayCountdown(void)
{
  displayClr();

  display4Strings("    Game will", "    start in:", "        3", "");

  quicksleep(6000000);

  display_string(2, "        2");
  display_update();

  quicksleep(6000000);

  display_string(2, "        1");
  display_update();

  quicksleep(6000000);

  displayClr();
} */