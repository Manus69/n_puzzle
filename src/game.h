#ifndef GAME_H
#define GAME_H

#include "why_lib.h"

#include "definitions.h"

extern Game* _game;

typedef struct Game Game;

struct Game
{
    HashTable*  boards;
    Board*      solved_board;
    byte        BOARD_SIDE_SIZE;
    byte        BOARD_TOTAL_SIZE;
    byte        CELL_SIZE;
};

#endif