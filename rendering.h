

#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000

void draw_rectangle(int xpos, int ypos, int width, int height);

void display_update();

void display_pixel(int xPos, int yPos);

void display_ball(double xPos, double yPos);

void window_init(char* window_name);

void display_paddle(double x, double y);