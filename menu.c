
#include "menu.h"
#include "rendering.h"
#include "input.h"
#include "gameloop.h"
#include <SDL2/SDL.h>

SDL_Event menu_event;

char *text_buffer[4];

void display_buffer(char *buffer[])
{
    display_4_strings(buffer[0], buffer[1], buffer[2], buffer[3]);
}

void menu_init()
{
    text_buffer[0] = "SDL Pong";
    text_buffer[1] = "Made by Casper Johansson";
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


        if(is_a_pressed())
        {
            menu_running = game_loop();
        }


        display_buffer(text_buffer);
    }
}










