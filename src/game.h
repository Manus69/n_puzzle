#ifndef GAME_H
#define GAME_H

#include "why_lib.h"
#include "board.h"

#include "definitions.h"

extern Game* _game;

struct Game
{
    byte        BOARD_SIDE_SIZE;
    byte        BOARD_TOTAL_SIZE;
    HashTable*  boards;
};

#endif