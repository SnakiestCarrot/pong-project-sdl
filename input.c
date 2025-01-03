
#include "input.h"
#include <SDL2/SDL.h>

int is_a_pressed()
{
    const Uint8* current_key_states = SDL_GetKeyboardState(NULL);
    return current_key_states[SDL_SCANCODE_A];
}

int is_s_pressed()
{
    const Uint8* current_key_states = SDL_GetKeyboardState(NULL);
    return current_key_states[SDL_SCANCODE_S];
}

int is_d_pressed()
{
    const Uint8* current_key_states = SDL_GetKeyboardState(NULL);
    return current_key_states[SDL_SCANCODE_D];
}

int is_f_pressed()
{
    const Uint8* current_key_states = SDL_GetKeyboardState(NULL);
    return current_key_states[SDL_SCANCODE_F];
}