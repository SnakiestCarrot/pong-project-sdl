

#include <stdio.h>
#include <math.h>

#include "gameloop.h"
#include "gamelogic.h"
#include "input.h"
#include "rendering.h"
#include "structs.h"
#include "constants.h"
#include <SDL2/SDL.h>

SDL_Event event;

struct Ball game_ball;
struct Paddle right_paddle;
struct Paddle left_paddle;

// Initializes variables changed inside the game loop
// By Casper Johansson
void game_state_init(void)
{
    game_ball.posX = 64.0;
    game_ball.posY = 16.0;
    game_ball.speedX = -40.0 / FPS;
    game_ball.speedY = 0.0 / FPS;

    right_paddle.posX = 120;
    right_paddle.posY = 16;
    right_paddle.speedX = 0;
    right_paddle.speedY = 0;
    right_paddle.height = PADDLESIZE;

    left_paddle.posX = 8;
    left_paddle.posY = 16;
    left_paddle.speedX = 0;
    left_paddle.speedY = 0;
    left_paddle.height = PADDLESIZE;
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

        if (is_a_pressed() && right_paddle.posY > -1)
        {
            right_paddle.speedY = paddle_speed / 60.0;
        }
        else if (is_d_pressed() && (right_paddle.posY + 4) < 32)
        {
            right_paddle.speedY = -paddle_speed / 60.0;
        }
        else
        {
            right_paddle.speedY = 0;
        }

        if (game_ball.posX >= 127)
        {
            game_ball.speedX *= -1;
        }
        else if (game_ball.posX < 0)
        {
            game_ball.speedX *= -1;
        }

        // collision with upper and lower borders
        // if statements are split and pos updated in order to fix a bug
        // where the ball would sometimes go out of bounds
        if (game_ball.posY < 0)
        {
            game_ball.posY = 0.0;
            game_ball.speedY *= -1;
        }

        if (game_ball.posY >= 31)
        {
            game_ball.posY = 31.0;
            game_ball.speedY *= -1;
        }

        // Right paddle and wall collison detection
        if (right_paddle.posY < 0)
        {
            right_paddle.posY = 0;
        }
        else if ((right_paddle.posY + right_paddle.height) >= 32)
        {
            right_paddle.posY = 32 - (right_paddle.height + 1);
        }

        // Left paddle and wall collison detection
        if (left_paddle.posY < 0)
        {
            left_paddle.posY = 0;
        }
        else if ((left_paddle.posY + left_paddle.height) >= 32)
        {
            left_paddle.posY = 32 - (left_paddle.height + 1);
        }

        if (ball_paddle_collision(&right_paddle, &game_ball))
        {
            // Angle calculation
            double bounce_angle = calculate_bounce_angle(&right_paddle, &game_ball);
            // New speeds
            game_ball.speedX = -ball_max_speed * cos(bounce_angle);
            game_ball.speedY = ball_max_speed * -sin(bounce_angle);

            // TODO: add playermode 2

            // Adds speed at mode 2
            /*
            if (playerMode == 2){
                accelerator += 0.1;
            }
            */
        }

        if (ball_paddle_collision(&left_paddle, &game_ball))
        {
            // Angle calculation
            double bounce_angle = calculate_bounce_angle(&left_paddle, &game_ball);
            // New speeds
            game_ball.speedX = ball_max_speed * cos(bounce_angle);
            game_ball.speedY = ball_max_speed * -sin(bounce_angle);

            // Adds speed at mode 2
            /*
            if (playerMode == 2){
                accelerator += 0.1;
            }
            */
        }

        // Ball position update
        game_ball.posX += (game_ball.speedX);
        game_ball.posY += game_ball.speedY;

        // Right paddle position update
        right_paddle.posX += right_paddle.speedX;
        right_paddle.posY += right_paddle.speedY;

        // Left paddle position update
        left_paddle.posX += left_paddle.speedX;
        left_paddle.posY += left_paddle.speedY;

        display_paddle(&left_paddle);
        display_paddle(&right_paddle);

        display_ball(&game_ball);

        display_update();
    }
}
