#include "why_lib.h"
#include "definitions.h"
#include "game.h"

int_unsigned hash_board(const Board* board)
{
    return hash_bytesFL(board->values, _game->BOARD_TOTAL_SIZE);
}