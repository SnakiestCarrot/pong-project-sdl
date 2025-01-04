

#include "structs.h"

int ball_paddle_collision (struct Paddle *p, struct Ball *b);

double calculate_bounce_angle (struct Paddle *p, struct Ball *b);

void set_paddle_speed(double speed);

extern double paddle_speed;
extern double ball_max_speed;
