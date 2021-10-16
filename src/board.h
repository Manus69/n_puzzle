#ifndef BOARD_H
#define BOARD_H

#include "why_definitions.h"
#include "definitions.h"
#include "position.h"
// #include "inline_declarations.h"

struct Board
{
    Board*          previous;
    int_unsigned    hash_value;
    short           metric_value;
    byte            empty_position_index;
    byte            side_size;
};

#endif