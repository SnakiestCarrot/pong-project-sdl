
#include "menu.h"
#include "rendering.h"
#include "input.h"
#include "gameloop.h"
#include "gamelogic.h"
#include "constants.h"

#include <SDL2/SDL.h>


SDL_Event menu_event;

char *text_buffer[4];

/*Menu handling and display written by Casper Johansson and August Wikdahl
    except where specified.
*/

// Used for difficulty selection menu
char difficultyStr[2][16] = {
    "AI: Easy", "AI: Hard"
};

// Used for ball speed selection menu
char ballMaxSpeedStr[2][16] = {
    "Ball Spd: 85.0", "Ball Spd: 130.0"
};

// Used for player mode selection menu
char player_mode_str[4][25] = {
    "2 Players\n", "1 Player VS AI\n", "Increasing speed\n", "Multiple Balls\n"
};

// makes menu a bit simpler
char *ballStr = "Ball spd: 85.0";

void displaySplashMenu ( void ) {
    text_buffer[0] = "1: Play";
    text_buffer[1] = "2: HiScores";
    text_buffer[2] = "3: Options";
    text_buffer[3] = "4: Back";
}

void displayOptionsMenu ( void ) {
    text_buffer[0] = difficultyStr[difficulty];
    text_buffer[1] = ballStr;
    text_buffer[2] = player_mode_str[player_mode];
    text_buffer[3] = "4: Back";
}

void display_buffer(char *buffer[])
{
    display_4_strings(buffer[0], buffer[1], buffer[2], buffer[3]);
}

enum Menu_State menu_state = SPLASH;

void menu_init()
{
    menu_state = SPLASH;
}

void menu_loop()
{
    menu_init();
    int menu_running = 1;
    while (menu_running)
    {
        // Handle quitting
        while (SDL_PollEvent(&menu_event))
        {
            switch (menu_event.type)
            {
            case SDL_QUIT:
                menu_running = 0;
                break;
            default:
                break;
            }
        }


        menu_handler();
        display_buffer(text_buffer);
    }
}

void menu_handler ( void ) {
    // Backs out to splash menu
    

    if (is_f_pressed()) {
        menu_state = SPLASH;
        displaySplashMenu();
    }


    /*
        Splash menu cases
    */
    if (menu_state == SPLASH) {
        
        displaySplashMenu();

        if (is_a_pressed()) {
            game_loop();
        }

        /* if (is_s_pressed()) {
            menu_state = HISCORE;
            displayHiScoreMenu();
        } */

        if (is_d_pressed()) {
            menu_state = OPTIONS;
            displayOptionsMenu();
        }

        /* 
        if (getsw() == 0x8) {
            displayCredits();
        } 
        */
    }
  

    /*
        Highscore menu cases
    */



    /*
        Options menu cases
        by Casper Johansson and August Wikdahl.
    */
    if (menu_state == OPTIONS) {
        
        // changes AI difficulty
        if (is_a_pressed()) {
            difficulty = (difficulty == EASY ? HARD : EASY); // toggles difficulty

            text_buffer[0] = difficultyStr[difficulty];
        }

        // changes paddle speed
        if (is_s_pressed()) {
            ball_max_speed = (ball_max_speed == (85.0 / FPS) ? (130.0 / FPS) : (85.0 / FPS)); // toggles players paddle speed
            ballStr = (ball_max_speed == (85.0 / FPS) ? ballMaxSpeedStr[0] : ballMaxSpeedStr[1]);

            text_buffer[1] = ballStr;
        } 

        // changes player mode
        if (is_d_pressed()) {
            player_mode = (player_mode == 3 ? 0 : player_mode + 1); // toggles player mode
            text_buffer[2] = player_mode_str[player_mode];
        }
    }
}










