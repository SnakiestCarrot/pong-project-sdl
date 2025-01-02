

#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL2/SDL.h"

extern SDL_Window *window;
extern SDL_Surface *surface;

void window_init();

void display_update(void);

/*
  Helper function to handle drawing rectangles with SDL
*/
void draw_rectangle(SDL_Surface *surface, int xpos, int ypos, int width, int height);

// Change this to make ball larger, measured in pixels
extern int ballSize;

void display_string(int line, char *s);


/* display4Strings:

  Takes 4 strings as input and writes them to the corresponding line
  on the display, then updates the display so the display actually shows the strings
  Made by Casper Johansson.
*/
void display4Strings(char *line0, char *line1, char *line2, char *line3);


// Takes x and y-coordinate for a pixel and adds it to the screen surface.
void displayPixel(int xPos, int yPos);


/*
  Writes a rectangle ((ballSize)x(ballSize) pixels) with its upper left corner
  on the specified x and y coordinates into the display buffer

  Made by Casper Johansson
*/
void displayBall(double x, double y);

/*
  Writes a paddle into the display buffer with its
  top-most pixel on the specified x and y coordinates
  into the display buffer

  Made by Casper Johansson
*/
void displayPaddle(double x, double y);


void displayClr(void);


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



#endif