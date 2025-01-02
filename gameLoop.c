

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include "mipslab.h" /* Declatations for these labs */
#include <math.h>
#include "io.h"
#include "display.h"
#include "gameLogic.h"

/*
Game Loop for all game modes.
Written By Casper Johansson and August Wikdahl.
*/

// Main game loop for player modes 0-2.
// 0: Normal 2-Player Mode
// 1: 1-Player Mode
// 2: 2-Player Mode with increasing ball speeds
void gameLoop(void)
{

  // Separate game loop for player mode 3.
  /* if (playerMode == 3)
  {
    playerMode3();

    // Set menustate to splashmenu
    displaySplashMenu();
    menuState = 0;
    quicksleep(5000000);
    return;
  } */

  // Sets a slower base speed to player mode 2.
  /* if (playerMode == 2)
  {
    ballMaxSpeed = 1.0;
  } */

  gameStateInit();

  // Game Loop
  while (!rPressed() && (scoreLeft < scoreLimit && scoreRight < scoreLimit))
  {

    // Clear display from previous screen
    displayClr();

    // Ball and wall collision detection
    if (gameBall.posX >= 127)
    {
      scoreLeft++;
      //displayGameScore(scoreLeft, scoreRight);
      gameStateInit();
    }
    else if (gameBall.posX < 0)
    {
      scoreRight++;
      //displayGameScore(scoreLeft, scoreRight);
      gameStateInit();
    }

    // collision with upper and lower borders
    // if statements are split and pos updated in order to fix a bug
    // where the ball would sometimes go out of bounds
    if (gameBall.posY < 0)
    {
      gameBall.posY = 0.0;
      gameBall.speedY *= -1;
    }

    if (gameBall.posY >= 31)
    {
      gameBall.posY = 31.0;
      gameBall.speedY *= -1;
    }

    // Right paddle and wall collison detection
    if (paddleR.posY < 0)
    {
      paddleR.posY = 0;
    }
    else if ((paddleR.posY + paddleR.height) >= 32)
    {
      paddleR.posY = 32 - (paddleR.height + 1);
    }

    // Left paddle and wall collison detection
    if (paddleL.posY < 0)
    {
      paddleL.posY = 0;
    }
    else if ((paddleL.posY + paddleL.height) >= 32)
    {
      paddleL.posY = 32 - (paddleL.height + 1);
    }

    // Needed for advanced project requirements
    if (ballTrajectoryAffectsGameplay == 1)
    {
      trajectoryModifier = 1.0 - (gameBall.speedY / ballMaxSpeed);
    }
    else
    {
      trajectoryModifier = 1.0;
    }

    // Right Paddle Collision
    if (ballPaddleCollide(&paddleR, &gameBall))
    {
      // Angle calculation
      double bounceAngle = calculateBounceAngle(&paddleR, &gameBall);
      // New speeds
      gameBall.speedX = -ballMaxSpeed * cos(bounceAngle);
      gameBall.speedY = ballMaxSpeed * -sin(bounceAngle);

      // Adds speed at mode 2
      /* if (playerMode == 2)
      {
        accelerator += 0.1;
      } */
    }

    // Left Paddle Collision
    if (ballPaddleCollide(&paddleL, &gameBall))
    {
      // Angle calculation
      double bounceAngle = calculateBounceAngle(&paddleL, &gameBall);
      // New speeds
      gameBall.speedX = ballMaxSpeed * cos(bounceAngle);
      gameBall.speedY = ballMaxSpeed * -sin(bounceAngle);

      // Adds speed at mode 2
      /* if (playerMode == 2)
      {
        accelerator += 0.1;
      } */
    }

    // Change the AI difficulty by changing its movement speed
    double paddleSpeedAI;

    /* if (difficulty == 0)
    {
      paddleSpeedAI = 30.0;
    }
    else if (difficulty == 1)
    {
      paddleSpeedAI = 45.0;
    } */

    // Right paddle movement for AI
    //if (playerMode == 1)
    //{
      int yPosCheck = gameBall.posY > paddleR.posY + (paddleR.height / 2);
      int boundsCheckUpper = paddleR.posY > -1;
      int boundsCheckLower = (paddleR.posY + 4) < 32;

      // Will wait until the player hits the paddle
      int waitForHit = gameBall.speedX > 0;

      if (yPosCheck && boundsCheckUpper && waitForHit)
      {
        paddleR.speedY = paddleSpeedAI / 60.0;
      }
      else if (~yPosCheck && boundsCheckLower && waitForHit)
      {
        paddleR.speedY = -paddleSpeedAI / 60.0;
      }
      else
      {
        paddleR.speedY = 0;
      }
    //}
    // Paddle movement for player
    //else if ((playerMode == 0) || (playerMode == 2))
    //{
      if (btn2pressed() && paddleR.posY > -1)
      {
        paddleR.speedY = 40.0 / 60.0;
      }
      else if (btn1pressed() && (paddleR.posY + 4) < 32)
      {
        paddleR.speedY = -40.0 / 60.0;
      }
      else
      {
        paddleR.speedY = 0;
      }
    //}

    // Left paddle movement
    if (btn4pressed() && paddleL.posY > -1)
    {
      paddleL.speedY = 40.0 / 60.0;
    }
    else if (btn3pressed() && (paddleL.posY + 4) < 32)
    {
      paddleL.speedY = -40.0 / 60.0;
    }
    else
    {
      paddleL.speedY = 0;
    }

    // Ball position update
    gameBall.posX += (gameBall.speedX * accelerator);
    gameBall.posY += gameBall.speedY;

    // Right paddle position update
    paddleR.posX += paddleR.speedX;
    paddleR.posY += paddleR.speedY;

    // Left paddle position update
    paddleL.posX += paddleL.speedX;
    paddleL.posY += paddleL.speedY;

    // Paddle pixels being written to displayBuffer
    displayPaddle(paddleR.posX, paddleR.posY); // Right paddle
    displayPaddle(paddleL.posX, paddleL.posY); // Left paddle

    // Ball pixels being written to displayBuffer
    displayBall(gameBall.posX, gameBall.posY);
  }

  /* displayWinnerScreen();
  if (playerMode == 1) {
    highScoreHandler(scoreLeft, scoreRight);
  } */

  // Reset scores
  scoreLeft = 0;
  scoreRight = 0;
  /*
    // Set menustate to splashmenu
    displaySplashMenu();
    menuState = 0;
    quicksleep(5000000); */
}

// Separate loop for Player Mode 3, using multiple balls.
// by August Wikdahl, reusing some code from main game loop

/* void playerMode3( void ){
    ballMaxSpeed = 0.5;

    //Multiple balls
    balls[0] = &ball1;
    balls[1] = &ball2;
    balls[2] = &ball3;
    balls[3] = &ball4;
    balls[4] = &ball5;
    ballsInit();

    //Set maximum amount of balls
    //3 seems to be the sweetspot for difficulty yet playable (and bug-free)
    maxBalls = 3;

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

      displayClr();

      //Update : checks end collision with all balls
      for (i = 0; i < noOfBalls; i++){
        if (balls[i]->posX >= 127) {
          scoreLeft++;
          displayGameScore();
          gameStateInit();
          ballsInit();
        }
        else if (balls[i]->posX < 0) {
          scoreRight++;
          displayGameScore();
          gameStateInit();
          ballsInit();
        }
      }

      //Update : checks border collision with all balls
      for (i = 0; i < noOfBalls; i++){
        if (balls[i]->posY < 0) {
          balls[i]->posY = 0.0;
          balls[i]->speedY *= -1;
        }
        if (balls[i]->posY >= 31) {
          balls[i]->posY = 31.0;
          balls[i]->speedY *= -1;
        }
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

      // Needed for advanced project requirements
      if (ballTrajectoryAffectsGameplay == 1) {
        trajectoryModifier = 1.0 - (gameBall.speedY / ballMaxSpeed);
      } else {
        trajectoryModifier = 1.0;
      }

      //Update : Left and Right paddle collision with all balls.
      for (i = noOfBalls; i >= 0; i--){
        if (ballPaddleCollide(&paddleR, balls[i])) {
          double bounceAngle = calculateBounceAngle(&paddleR, balls[i]);

          balls[i]->speedX = -ballMaxSpeed * (cos(bounceAngle));
          balls[i]->speedY = ballMaxSpeed * (-sin(bounceAngle));
          if (noOfBalls < maxBalls){
            noOfBalls ++;
          }
        }
      }
      for (i = noOfBalls; i >= 0; i--){
        if (ballPaddleCollide(&paddleL, balls[i])) {
          double bounceAngle = calculateBounceAngle(&paddleL, balls[i]);

          balls[i]->speedX = ballMaxSpeed * cos(bounceAngle);
          balls[i]->speedY = ballMaxSpeed * -sin(bounceAngle);
          if (noOfBalls < maxBalls){
            noOfBalls ++;
          }
        }
      }

      // Change the AI difficulty by changing its movement speed
      double paddleSpeedAI;

      if (difficulty == 0) {
        paddleSpeedAI = 30.0;
      } else if (difficulty == 1) {
        paddleSpeedAI = 45.0;
      }

      // Right paddle movement for AI
      if (playerMode == 0) {
        int yPosCheck = gameBall.posY > paddleR.posY + (paddleR.height / 2);
        int boundsCheckUpper = paddleR.posY > -1;
        int boundsCheckLower = (paddleR.posY + 4) < 32;

        // Will wait until the player hits the paddle
        int waitForHit = gameBall.speedX > 0;

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
      else if (playerMode == 3) {
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

      //Update : updates positions of all balls
      for (i = 0; i < noOfBalls; i++){
        balls[i]->posX += balls[i]->speedX;
        balls[i]->posY += balls[i]->speedY;
      }

      // Right paddle position update
      paddleR.posX += paddleR.speedX;
      paddleR.posY += paddleR.speedY;

      // Left paddle position update
      paddleL.posX += paddleL.speedX;
      paddleL.posY += paddleL.speedY;

      // Paddle pixels being written to displayBuffer
      displayPaddle(paddleR.posX, paddleR.posY);  // Right paddle
      displayPaddle(paddleL.posX, paddleL.posY);  // Left paddle

      //Update : writes all position of all balls to display-buffer.
      for (i = 0; i < noOfBalls; i++) {
        displayBall(balls[i]->posX, balls[i]->posY);
      }

      // Sending the display buffer to OLED screen
      display_image(0, displayBuffer);
      timeoutcount = 0;
    }
  }

  displayWinnerScreen();
  // Reset scores
  scoreLeft = 0;
  scoreRight = 0;
} */