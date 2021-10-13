#ifndef STATE_H
#define STATE_H

#include "why_lib.h"
#include "definitions.h"

struct State
{
    Board*      current_board;
    Heap*       queue;
    HashTable*  used_boards;
    Array*      path;
};

#endif