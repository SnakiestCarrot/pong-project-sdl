
#include "rendering.h"
#include "input.h"
#include "gameloop.h"
#include "menu.h"

int main(int argc, char* argv[]) 
{
    window_init("Blank window");

    menu_loop();
    
	return 0;
}
