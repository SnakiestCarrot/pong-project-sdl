
#include <SDL2/SDL.h>

#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000

void draw_rectangle(SDL_Surface *surface, int xpos, int ypos, int width, int height);

void display_update(SDL_Window* window);

void display_pixel(SDL_Surface* surface, int xPos, int yPos);

void display_ball(SDL_Surface* surface, double xPos, double yPos);