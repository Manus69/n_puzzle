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

int_signed metric_mhtn_value_index(const Board* board, byte value, byte index)
{
    Position actual_position;
    Position intended_position;
    Position diff;

    actual_position = position_from_index(index, board->side_size);
    intended_position = get_intended_position(value, board->side_size);
    diff = position_diff(intended_position, actual_position);

    return position_vector_length(diff);
}

int_signed metric_mhtn(const Board* board)
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

int_signed metric_mhtn_after_swap(const Board* board, byte j, byte k)
{
    byte        lhs;
    byte        rhs;
    int_signed  increment;

    lhs = board_at(board, k);
    rhs = board_at(board, j);
    increment = metric_mhtn_value_index(board, rhs, j)
                - metric_mhtn_value_index(board, lhs, j)
                + metric_mhtn_value_index(board, lhs, k)
                - metric_mhtn_value_index(board, rhs, k);

    return board->metric_value + increment;
}

int_signed metric_misplaced(const Board* board)
{
    return count_misplaced_elements(board);
}

static bool _misplaced_after_swap(const Board* board, byte j, byte k)
{
    byte value;

    value = board_at(board, j);
    if (get_intended_index(value, board->side_size) == k)
        return false;
    
    return true;
}

int_signed metric_misplaced_after_swap(const Board* board, byte j, byte k)
{
    int_signed increment;

    increment = 0;
    increment += _misplaced_after_swap(board, j, k) ? 1 : -1;
    increment += _misplaced_after_swap(board, k, j) ? 1 : -1;

    return board->metric_value + increment;
}

int_signed metric_uniform(const Board* board)
{
    no_op((void *)board);

    return 0;
}

int_signed metric_uniform_after_swap(const Board* board, byte j, byte k)
{
    no_op((void *)board);
    SWAP(j, k, byte);

    return 0; 
}