
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include "io.h"
#include "display.h"
#include "gameLoop.h"

#define FPS 144

int main(int argc, char* argv[]) {
	
	printf("HELLO WORLD!");

   window_init();

   SDL_Event event;

   int running = 1;

   while (running)
   {
      while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                default:
                    break;
            }
        }
      printf("%d\n", btn1pressed());

      displayPixel(3, 3);

      gameLoop();

      SDL_Delay(1000/FPS);

      display_update();
   }
   

	return 0;
}
