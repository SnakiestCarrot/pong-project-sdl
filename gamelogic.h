

#include "structs.h"
#include "constants.h"

int ball_paddle_collision (struct Paddle *p, struct Ball *b);

double calculate_bounce_angle (struct Paddle *p, struct Ball *b);

void move_paddle(struct Paddle *p, int (*up_button_is_pressed)(void), int (*down_button_is_pressed)(void));

void update_ball_position(struct Ball *b);

void update_paddle_position(struct Paddle *p);

extern double paddle_speed;
extern double ball_max_speed;
extern int player_mode;
extern enum Difficulty difficulty;
