

all:
	gcc -O0 -m64 -I ./src/include -L ./src/lib -o main main.c display.c io.c gameLogic.c gameLoop.c -lmingw32 -lSDL2main -lSDL2