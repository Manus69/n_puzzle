#ifndef GAME_H
#define GAME_H

#include "why_definitions.h"
#include "definitions.h"

#include <time.h>

struct Game
{
    Board*      solved_board;
    Board*      initial_board;
    HashTable*  boards;
    HashTable*  visited_boards;

    Board*      current_board;
    Heap*       queue;

    int_signed  (*metric)(const Board *);
    int_signed  (*metric_increment)(const Board* board, byte j, byte k);
    
    byte        BOARD_SIDE_SIZE;
    byte        BOARD_TOTAL_SIZE;

    clock_t     time_of_creation;
};

#endif