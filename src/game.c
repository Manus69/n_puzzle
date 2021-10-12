#include "game.h"

byte BOARD_SIZE;

byte board_size_set(byte size)
{
    BOARD_SIZE = size;

    return BOARD_SIZE;
}