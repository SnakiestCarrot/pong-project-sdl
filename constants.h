
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define ORIGINAL_WIDTH 128
#define ORIGINAL_HEIGHT 32

#define SCREEN_SCALING 14
#define SCREEN_WIDTH (ORIGINAL_WIDTH*SCREEN_SCALING)
#define SCREEN_HEIGHT (ORIGINAL_HEIGHT*SCREEN_SCALING)

#define FPS 144

enum Difficulty {
    EASY,
    HARD
};

enum Menu_State {
    SPLASH,
    HISCORE,
    OPTIONS
};

enum Player_Mode {
    TWOPLAYER,
    ONEPLAYER,
    INCREASINGSPEED,
    MULTIPLEBALLS
};

extern const int BALLSIZE;
extern const int PADDLESIZE;

#endif // CONSTANTS_H