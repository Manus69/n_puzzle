#ifndef BOARD_H
#define BOARD_H

#include "why_lib.h"
#include "game.h"

struct Board
{
    byte*   values;
    byte*   empty_position_index;
};

typedef struct Board Board;

Board* board_create(byte* values);
byte board_at(const Board* board, byte n);
byte board_atG(const Board* board, byte row, byte col);

#endif