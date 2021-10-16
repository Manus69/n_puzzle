#ifndef GAME_H
#define GAME_H

#include "why_definitions.h"
#include "definitions.h"

struct Game
{
    Board*      solved_board;
    HashTable*  boards;
    HashTable*  visited_boards;

    Board*      current_board;
    Heap*       queue;

    int_signed  (*metric)(const Board *);
    byte        BOARD_SIDE_SIZE;
    byte        BOARD_TOTAL_SIZE;
};

#endif