#include "why_lib.h"
#include "definitions.h"
#include "declarations.h"
#include "game.h"
#include "board_inline.h"

int_unsigned hash_board_size(const Board* board, int_signed size)
{
    return hash_bytesFL(board_get_values(board), size);
}

int_unsigned hash_board(const Board* board)
{
    return hash_board_size(board, board->side_size * board->side_size);
}