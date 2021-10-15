#ifndef STATE_H
#define STATE_H

#include "why_lib.h"
#include "definitions.h"

struct State
{
    Board*      current_board;
    Heap*       queue;
    HashTable*  used_boards;

    int_signed  (*queue_compare_function)();
    int_signed  (*metric)(const Board *);
    int_signed  metric_value;
};

#endif