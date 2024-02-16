

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <math.h>

/*
 gameLogic.c

 Handles logic of the game, such as movement, positions, collisions etc. 

 Made by Casper Johansson
*/

/*
  struct to track ball parameters
*/ 
struct Ball {
  double posX;
  double posY;
  double speedX;
  double speedY;
};


/*
  struct for the paddles
*/
struct Paddle {
  double posX;
  double posY;
  double speedX;
  double speedY;
  int height;
};

// set the default paddle height here
int defaultPaddleHeight = 8;

// creating ball and paddles
struct Ball gameBall1;
struct Paddle paddleR;
struct Paddle paddleL;

// Tracks the score for the left side paddle (Player)
int scoreLeft = 0;

// Tracks the score for the right side paddle (Player or AI)
int scoreRight = 0;

// Decides at what score to end the game
int scoreLimit = 10;

// Determines the sensitivity of the ball bouncing of the paddles
const double bounciness = (1.2 * 3.1415) / 5;

// Determines the maximum speed at which the ball will 
// travel at as a combined speed for the x and y vectors.
double ballMaxSpeed;

// Hitbox safety margin
double hitboxSize = 1.0;

// Initializes variables changed inside the game loop
void gameStateInit ( void ) {
  gameBall1.posX = 64.0;
  gameBall1.posY = 16.0;
  gameBall1.speedX = -40.0 / 60.0;
  gameBall1.speedY = 5.0 / 60.0;

  paddleR.posX = 120;
  paddleR.posY = 16;
  paddleR.speedX = 0;
  paddleR.speedY = 0;
  paddleR.height = defaultPaddleHeight;

  
  paddleL.posX = 8;
  paddleL.posY = 16;
  paddleL.speedX = 0;
  paddleL.speedY = 0;
  paddleL.height = defaultPaddleHeight;
}

//function for calculating bounce angle:
      /* double calculateBounceAngle (struct Paddle paddle) {
        double relativeY = (paddle.posY + (paddle.height/2)) - gameBall1.posY;
        double intersectCoefficient = relativeY / (paddle.height / 2);
        return = intersectCoefficient * bounciness;
      } */

      //functions for testing ball collision
      // int ballPaddleCollide (struct Paddle paddle) {

      // int ballPaddleXCollide = (paddle.posX - hitboxSize <= gameBall1.posX + hitboxSize &&
      //                             paddle.posX + hitboxSize >= gameBall1.posX - hitboxSize);
      // int ballPaddleYCollide = ((paddle.posY - hitboxSize <= gameBall1.posY + hitboxSize) &&
      //                             (paddle.posY + paddle.height + hitboxSize) >= gameBall1.posY - hitboxSize);

void gameLoop ( void ) {
  int timeoutcount = 0;

  gameStateInit();
  
  while (getsw() != 0x1 && (scoreLeft < scoreLimit && scoreRight < scoreLimit)) {

    // usage of the timer from lab 3
    if (IFS(0) & 0x100) {
      timeoutcount++;
      IFSCLR(0) = 0x100;
    }

    // When timer gives an interrupt, do a game update
    if (timeoutcount == 1) {
      
      // Clear displayBuffer from previous screen
      displayClr();

      // Ball and wall collision detection
      if (gameBall1.posX >= 127) {
        scoreLeft++;
        displayGameScore();
        gameStateInit();
      } 
      else if (gameBall1.posX < 0) {
        scoreRight++;
        displayGameScore();
        gameStateInit();
      }

      // collision with upper and lower borders
      // if statements are split and pos updated in order to fix a bug
      // where the ball would sometimes go out of bounds
      if (gameBall1.posY < 0) {
        gameBall1.posY = 0.0;
        gameBall1.speedY *= -1;
      }

      if (gameBall1.posY >= 31) {
        gameBall1.posY = 31.0;
        gameBall1.speedY *= -1;
      }

      // Right paddle and wall collison detection
      if (paddleR.posY < 0) {
        paddleR.posY = 0;
      } 
      else if ((paddleR.posY + paddleR.height) >= 32) {
        paddleR.posY = 32 - (paddleR.height + 1);
      }

      // Left paddle and wall collison detection
      if (paddleL.posY < 0) {
        paddleL.posY = 0;
      } 
      else if ((paddleL.posY + paddleL.height) >= 32) {
        paddleL.posY = 32 - (paddleL.height + 1);
      }

      // Uses the Y speed of the ball to modify the final angle of reflection of the ball
      // We can use only the Y speed since we have the constant speed of the balls total vector (ballMaxSpeed)
      // from a gameplay perspective it is not very good, but it is a requirement for an advanced project

      // The shallower the angle the less effect it will have
      
      int ballTrajectoryAffectsGameplay = 1; // turn on or off if the ball trajectory affects gameplay
      double trajectoryModifier;
      
      // Needed for advanced project requirements
      if (ballTrajectoryAffectsGameplay == 1) { 
        trajectoryModifier = 1.0 - (gameBall1.speedY / ballMaxSpeed);  
      } else {
        trajectoryModifier = 1.0;
      }
      
      
      // Right paddle and ball collision detection - Remove this block
      int ballRPaddleXCollide = (paddleR.posX - hitboxSize <= gameBall1.posX + hitboxSize &&
                                  paddleR.posX + hitboxSize >= gameBall1.posX - hitboxSize);
      int ballRPaddleYCollide = ((paddleR.posY - hitboxSize <= gameBall1.posY + hitboxSize) &&
                                  (paddleR.posY + paddleR.height + hitboxSize) >= gameBall1.posY - hitboxSize);

      int ballRPaddleCollision = ballRPaddleXCollide && ballRPaddleYCollide; //would become - intballRPaddleCollision = ballPaddleCollide(paddleR);

      // Left paddle and ball collision detection - do the same with left
      int ballLPaddleXCollide = (paddleL.posX - hitboxSize <= gameBall1.posX + hitboxSize &&
                                  paddleL.posX + hitboxSize >= gameBall1.posX - hitboxSize);
      int ballLPaddleYCollide = ((paddleL.posY - hitboxSize <= gameBall1.posY + hitboxSize) && 
                                  (paddleL.posY + paddleR.height + hitboxSize) >= gameBall1.posY - hitboxSize);

      int ballLPaddleCollision = ballLPaddleXCollide && ballLPaddleYCollide;

      if (ballRPaddleCollision) {
        // Angle calculation 
        double relativeY = (paddleR.posY + (paddleR.height/2)) - gameBall1.posY;
        double intersectCoefficient = (relativeY / (paddleR.height / 2)) * trajectoryModifier;
        double bounceAngle = intersectCoefficient * bounciness;

        // New speeds
        gameBall1.speedX = -ballMaxSpeed * cos(bounceAngle);
        gameBall1.speedY = ballMaxSpeed * -sin(bounceAngle);
      }

      if (ballLPaddleCollision) {
        // Angle calculation
        double relativeY = (paddleL.posY + (paddleL.height/2)) - gameBall1.posY;
        double intersectCoefficient = (relativeY / (paddleL.height / 2)) * trajectoryModifier;
        double bounceAngle = intersectCoefficient * bounciness;

        // New speeds
        gameBall1.speedX = ballMaxSpeed * cos(bounceAngle);
        gameBall1.speedY = ballMaxSpeed * -sin(bounceAngle);
      }

      // Change the AI difficulty by changing its movement speed
      double paddleSpeedAI;
      
      if (difficulty == 0) {
        paddleSpeedAI = 30.0;
      } else if (difficulty == 1) {
        paddleSpeedAI = 40.0;
      }
      
      // Right paddle movement for AI
      if (playerMode == 1) {
        int yPosCheck = gameBall1.posY > paddleR.posY + (paddleR.height / 2);
        int boundsCheckUpper = paddleR.posY > -1;
        int boundsCheckLower = (paddleR.posY + 4) < 32;

        // Will wait until the player hits the paddle
        int waitForHit = gameBall1.speedX > 0;

        if (yPosCheck && boundsCheckUpper && waitForHit) {
          paddleR.speedY = paddleSpeedAI / 60.0;
        } 
        else if (~yPosCheck && boundsCheckLower && waitForHit) {
          paddleR.speedY = -paddleSpeedAI / 60.0;
        } 
        else {
          paddleR.speedY = 0;
        }
      } 
      // Paddle movement for player
      else if (playerMode == 0) {
        if (btn2pressed() && paddleR.posY > -1) {
          paddleR.speedY = paddleSpeed / 60.0;
        } 
        else if (btn1pressed() && (paddleR.posY + 4) < 32) {
          paddleR.speedY = -paddleSpeed / 60.0;
        } 
        else {
          paddleR.speedY = 0;
        }
      }

      // Left paddle movement
      if (btn4pressed() && paddleL.posY > -1) {
        paddleL.speedY = paddleSpeed / 60.0;
      } 
      else if (btn3pressed() && (paddleL.posY + 4) < 32) {
        paddleL.speedY = -paddleSpeed / 60.0;
      } 
      else {
        paddleL.speedY = 0;
      }

      //function for updating all positions:
      // void updatePosition(struct object) {
      //   object.posX += object.speedx;
      //   object.posY += object.speedY;
      // }

      //Update next statements to:
      //updatePosition(gameBall1);
      //updatePosition(paddleR);
      //updatePosition(paddleL);
   
      // Ball position update
      gameBall1.posX += gameBall1.speedX;
      gameBall1.posY += gameBall1.speedY;

      // Right paddle position update
      paddleR.posX += paddleR.speedX;
      paddleR.posY += paddleR.speedY;

      // Left paddle position update
      paddleL.posX += paddleL.speedX;
      paddleL.posY += paddleL.speedY;

      // Paddle pixels being written to displayBuffer
      displayPaddle(paddleR.posX, paddleR.posY);  // Right paddle
      displayPaddle(paddleL.posX, paddleL.posY);  // Left paddle

      // Ball pixels being written to displayBuffer
      displayBall(gameBall1.posX, gameBall1.posY);

      // Sending the display buffer to OLED screen
      display_image(0, displayBuffer);
      timeoutcount = 0;
    }
  }
  
  displayWinnerScreen();
  if (playerMode == 1) {
    highScoreHandler(scoreLeft, scoreRight);
  }
  
  // Reset scores
  scoreLeft = 0;
  scoreRight = 0;

  // Set menustate to splashmenu
  displaySplashMenu();
  menuState = 0;
  quicksleep(5000000);
}

