
#include <stdint.h>
#include <SDL2/SDL.h>
#include "io.h"

/*Functions for Input.
Written by August Wikdahl and Casper Johansson from previous labs, 
reused for the mini project*/

/* btn4pressed:
returns 1 as an int if btn4 is pressed, else 0
*/ 
int btn4pressed ( void ) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    return currentKeyStates[SDL_SCANCODE_A];
}

/* btn3pressed:
returns 1 as an int if btn3 is pressed, else 0
*/
int btn3pressed ( void ) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    return currentKeyStates[SDL_SCANCODE_S];
}

/* btn2pressed:
returns 1 as an int if btn2 is pressed, else 0
*/
int btn2pressed ( void ) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    return currentKeyStates[SDL_SCANCODE_D];
}

/* btn1pressed:
returns 1 as an int if btn1 is pressed, else 0
*/
int btn1pressed ( void ) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    return currentKeyStates[SDL_SCANCODE_F];
}

int rPressed ( void ) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    return currentKeyStates[SDL_SCANCODE_R];
}