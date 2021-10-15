#ifndef GAME_H
#define GAME_H

#include "why_definitions.h"
#include "definitions.h"

extern Game* _game;

struct Game
{
    HashTable*  boards;
    Board*      solved_board;
    byte        BOARD_SIDE_SIZE;
    byte        BOARD_TOTAL_SIZE;
    byte        CELL_SIZE;
};

#endif