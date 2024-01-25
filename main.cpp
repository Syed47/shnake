#include "game.h"

#ifndef _PARAMS_
    #define ROWS 60
    #define COLS 60
    #define GENERATIONS 5000 // total number of generations
    #define RATE 100 // generation per second
    #define CELL_SIZE 12
    #define Y_OFFSET 40
    #define WIN_WIDTH (BLOCK_SIZE * ROWS)
    #define WIN_HEIGHT (BLOCK_SIZE * COLS + Y_OFFSET)
#endif


int main(int argc, char const *argv[])
{

    game shnake_game(ROWS, COLS, CELL_SIZE);
    shnake_game.start();
    return 0;
}
