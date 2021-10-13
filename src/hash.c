#include "why_lib.h"
#include "definitions.h"
#include "game.h"
#include "board.h"

int_unsigned hash_board_size(const Board* board, int_signed size)
{
    return hash_bytesFL(board->values, size);
}

int_unsigned hash_board(const Board* board)
{
    return hash_board_size(board, _game->BOARD_TOTAL_SIZE);
}