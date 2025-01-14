
#include "structs.h"

#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000

void draw_rectangle(int xpos, int ypos, int width, int height);

void display_update();

void display_pixel(int xPos, int yPos);

void display_ball(struct Ball *ball);

void display_paddle(struct Paddle *paddle);

void window_init(char* window_name);

void display_string(int line, char *text);

void display_4_strings(char *line0, char *line1, char *line2, char *line3);

void display_buffer(char *buffer[]);
