


#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "SDL2/SDL.h"
#include <stdint.h>  /* Declarations of uint_32 and the like */
#include "mipslab.h" /* Declatations for these labs */
#include <math.h>
#include "io.h"
#include "display.h"
#include "gameLogic.h"
#include "gameObjects.h"

/*
Game Loop for all game modes.
Written By Casper Johansson and August Wikdahl.
*/

// Main game loop for player modes 0-2.
// 0: Normal 2-Player Mode
// 1: 1-Player Mode
// 2: 2-Player Mode with increasing ball speeds
void gameLoop(void);


// Separate loop for Player Mode 3, using multiple balls.
// by August Wikdahl, reusing some code from main game loop

/* 
void playerMode3( void )
*/



#endif