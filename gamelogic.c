
#include "constants.h"
#include "structs.h"
#include "gamelogic.h"

// Hitbox safety margin
const double HITBOX_SIZE = 1.0;

// Determines the sensitivity of the ball bouncing of the paddles
// it is essentially the maximum angle the ball can bounce at from horizontal
const double bounciness = (1.2 * 3.1415) / 5;

double ball_max_speed = 85.0 / FPS;

double paddle_speed = 60.0 / FPS;

double trajectoryModifier = 1.0;

double paddle_speed_ai = 30.0 / FPS;

enum Difficulty difficulty = EASY;

enum Player_Mode player_mode = TWOPLAYER;

int ball_paddle_collision(struct Paddle *p, struct Ball *b)
{
  int ballPaddleXCollide = ((p->posX) - HITBOX_SIZE <= (b->posX) + HITBOX_SIZE &&
                            (p->posX) + HITBOX_SIZE >= (b->posX) - HITBOX_SIZE);
  int ballPaddleYCollide = (((p->posY) - HITBOX_SIZE <= (b->posY) + HITBOX_SIZE) &&
                            ((p->posY) + (p->height) + HITBOX_SIZE) >= (b->posY) - HITBOX_SIZE);

  int ballPaddleCollision = ballPaddleXCollide && ballPaddleYCollide;
  return ballPaddleCollision;
}

double calculate_bounce_angle(struct Paddle *p, struct Ball *b)
{
  double relativeY = ((p->posY) + ((p->height) / 2)) - (b->posY);
  double intersect_coefficient = (relativeY / ((p->height) / 2)) * trajectoryModifier;
  double bounce_angle = intersect_coefficient * bounciness;
  return bounce_angle;
}

void move_paddle(struct Paddle *p, int (*up_button_is_pressed)(void), int (*down_button_is_pressed)(void))
{
  if (down_button_is_pressed() && p->posY > -1)
  {
    p->speedY = paddle_speed;
  }
  else if (up_button_is_pressed() && (p->posY + 4) < ORIGINAL_HEIGHT)
  {
    p->speedY = -paddle_speed;
  }
  else
  {
    p->speedY = 0;
  }
}

void ai_move_paddle(struct Ball *b, struct Paddle *p)
{
  int yPosCheck = b->posY > p->posY + (p->height / 2);
  int boundsCheckUpper = p->posY > -1;
  int boundsCheckLower = (p->posY + 4) < 32;

  // Will wait until the player hits the ball
  int waitForHit = b->speedX > 0;

  if (yPosCheck && boundsCheckUpper && waitForHit)
  {
    p->speedY = paddle_speed_ai;
  }
  else if (~yPosCheck && boundsCheckLower && waitForHit)
  {
    p->speedY = -paddle_speed_ai;
  }
  else
  {
    p->speedY = 0;
  }
}

void update_ball_position(struct Ball *b)
{
  b->posX += b->speedX;
  b->posY += b->speedY;
}

void update_paddle_position(struct Paddle *p)
{
  p->posX += p->speedX;
  p->posY += p->speedY;
}
