

#include <stdio.h>

#include "gameloop.h"
#include "rendering.h"
#include "structs.h"
#include "constants.h"
#include <SDL2/SDL.h>

SDL_Event event;

struct Ball game_ball;

// Initializes variables changed inside the game loop
// By Casper Johansson
void game_state_init ( void ) {
  game_ball.posX = 64.0;
  game_ball.posY = 16.0;
  game_ball.speedX = -40.0 / FPS;
  game_ball.speedY = 0.0 / FPS;
}

void game_loop()
{
    game_state_init();
    int running = 1;
    while (running)
    {
        // Handle quitting
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            default:
                break;
            }
        }
        display_paddle(3.0,3.0);

        display_ball(game_ball.posX, game_ball.posY);

        display_update();
    }
}
