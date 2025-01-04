
#include "structs.h"
#include "gamelogic.h"

// Hitbox safety margin
const double hitbox_size = 1.0;

// Determines the sensitivity of the ball bouncing of the paddles
// it is essentially the maximum angle the ball can bounce at from horizontal
const double bounciness = (1.2 * 3.1415) / 5;


double ball_max_speed = 1.0;

double paddle_speed = 40.0;

double trajectoryModifier = 1.0;

void set_paddle_speed(double speed)
{
    paddle_speed = speed;
}

int ball_paddle_collision (struct Paddle *p, struct Ball *b)
{
  int ballPaddleXCollide = ((p->posX) - hitbox_size <= (b->posX) + hitbox_size &&
                              (p->posX) + hitbox_size >= (b->posX) - hitbox_size);
  int ballPaddleYCollide = (((p->posY) - hitbox_size <= (b->posY) + hitbox_size) &&
                              ((p->posY) + (p->height) + hitbox_size) >= (b->posY) - hitbox_size);

  int ballPaddleCollision = ballPaddleXCollide && ballPaddleYCollide;
  return ballPaddleCollision;
}

double calculate_bounce_angle (struct Paddle *p, struct Ball *b)
{
  double relativeY = ((p->posY) + ((p->height)/2)) - (b->posY);
  double intersectCoefficient = (relativeY / ((p->height) / 2)) * trajectoryModifier;
  double bounceAngle = intersectCoefficient * bounciness;
  return bounceAngle;
}



