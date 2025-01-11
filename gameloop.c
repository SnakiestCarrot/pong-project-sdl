

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

int game_loop()
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
                return 0;
                break;
            default:
                break;
            }
        }

        if(is_q_pressed())
        {
            running = 0;
        }

        move_paddle(&left_paddle, is_a_pressed, is_s_pressed);
        move_paddle(&right_paddle, is_d_pressed, is_f_pressed);

        if (game_ball.posX >= ORIGINAL_WIDTH)
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

        if (game_ball.posY >= ORIGINAL_HEIGHT-1)
        {
            game_ball.posY = ORIGINAL_HEIGHT-1;
            game_ball.speedY *= -1;
        }

        // Right paddle and wall collison detection
        if (right_paddle.posY < 0)
        {
            right_paddle.posY = 0;
        }
        else if ((right_paddle.posY + right_paddle.height) >= ORIGINAL_HEIGHT)
        {
            right_paddle.posY = ORIGINAL_HEIGHT - (right_paddle.height);
        }

        // Left paddle and wall collison detection
        if (left_paddle.posY < 0)
        {
            left_paddle.posY = 0;
        }
        else if ((left_paddle.posY + left_paddle.height) >= 32)
        {
            left_paddle.posY = 32 - (left_paddle.height);
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

            // TODO: add playermode 2
            // Adds speed at mode 2
            /*
            if (playerMode == 2){
                accelerator += 0.1;
            }
            */
        }

        // Ball position update
        update_ball_position(&game_ball);
        
        // Right paddle position update
        update_paddle_position(&right_paddle);

        // Left paddle position update
        update_paddle_position(&left_paddle);

        display_paddle(&left_paddle);
        display_paddle(&right_paddle);

        display_ball(&game_ball);

        display_update();
    }
    return 1;
}
