#ifndef GAME_H
#define GAME_H

#include "why_definitions.h"
#include <limits.h>

#define EMPTY_CELL_VALUE 0
#define MAX_VALUE (1 << (sizeof(byte) * CHAR_BIT))

extern byte BOARD_SIZE;

byte board_size_set(byte size);

#endif