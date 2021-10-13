#ifndef BOARD_H
#define BOARD_H

#include "why_lib.h"
#include "game.h"

struct Board
{
    Board*          previous;
    byte*           values;
    int_unsigned    hash_value;
    byte            empty_position_index;
};

#endif