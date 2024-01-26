#include "game.h"

#ifndef _PARAMS_
    #define ROWS 20
    #define COLS 20
    #define CELL_SIZE 20
#endif


int main(int argc, char const *argv[])
{

    game shnake_game(ROWS, COLS, CELL_SIZE);
    shnake_game.start();
    return 0;
}
