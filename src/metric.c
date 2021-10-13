#include "why_lib.h"
#include "definitions.h"
#include "declarations.h"
#include "game.h"

int_signed metric_manhattan(const Board* board)
{
    byte row;
    byte col;

    row = board_row_of_zero(board);
    col = board_col_of_zero(board);

    return 2 * _game->BOARD_SIDE_SIZE - (row + col) - 2;
}

int_signed metric_manhattanN(const Board* board)
{
    return -metric_manhattan(board);
}