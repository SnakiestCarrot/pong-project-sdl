

#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <math.h>
#include "gameLogic.h"
#include "gameObjects.h"
#include "gameConstants.h"

// set the default paddle height here


// creating ball and paddles
struct Ball gameBall;
struct Paddle paddleR;
struct Paddle paddleL;

// Tracks the score for the left side paddle (Player)
int scoreLeft;

// Tracks the score for the right side paddle (Player or AI)
int scoreRight;

// Decides at what score to end the game
int scoreLimit;

// Determines the sensitivity of the ball bouncing of the paddles
// it is essentially the maximum angle the ball can bounce at from horizontal
const double bounciness;

// Uses the Y speed of the ball to modify the final angle of reflection of the ball
// We can use only the Y speed since we have the constant speed of the balls total vector (ballMaxSpeed)
// from a gameplay perspective it is not very good, but it is a requirement for an advanced project
// The shallower the angle the less effect it will have
int ballTrajectoryAffectsGameplay; // turn on or off if the ball trajectory affects gameplay
double trajectoryModifier;

// Determines the maximum speed at which the ball will 
// travel at as a combined speed for the x and y vectors.
double ballMaxSpeed;

//Used for gamemode with increasing speed
//Increases with each paddle bounce, for other game modes stays at 1.0.
double accelerator;

// Hitbox safety margin
double hitboxSize;

//iterator
int i;

//Multiple balls for player mode 3
struct Ball ball1, ball2, ball3, ball4, ball5;
struct Ball *balls[5];

//Variables for balll count
int noOfBalls;
int maxBalls;

// Initializes variables changed inside the game loop
// By Casper Johansson
void gameStateInit ( void );

//Function for calculating bounce angle
double calculateBounceAngle (struct Paddle *p, struct Ball *b);

//Function for detecting ball and paddle collision
int ballPaddleCollide (struct Paddle *p, struct Ball *b);

//Initialize balls for player mode 3
//By August Wikdahl
void ballsInit();

#endif



