#include "why_definitions.h"
#include "definitions.h"
#include "declarations.h"
#include "game.h"
#include "board.h"
#include "board_inline.h"
#include "why_macros.h"

int_signed metric_mhtn_at_index(const Board* board, byte index)
{
    Position intended_position;
    Position actual_position;
    Position diff;

    intended_position = get_intended_position(board_at(board, index), board->side_size);
    actual_position = position_from_index(index, board->side_size);
    diff = position_diff(intended_position, actual_position);

    return position_vector_length(diff);
}

int_signed metric_mhtn_all(const Board* board)
{
    int_signed  total_distance;
    byte        index;
    byte        total_size;

    index = 0;
    total_distance = 0;
    total_size = board_get_total_size(board);

    while (index < total_size)
    {
        total_distance += metric_mhtn_at_index(board, index);
        index ++;
    }

    return total_distance;
}

int_signed metric_mhtn_zero(const Board* board)
{
    return metric_mhtn_at_index(board, board->empty_position_index);
}
