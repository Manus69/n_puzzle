#include "why_definitions.h"
#include "definitions.h"
#include "declarations.h"
#include "game.h"
#include "board.h"
#include "why_macros.h"

int_signed get_manhattan_distnace(const Board* board, byte index)
{
    Position intended_position;
    Position actual_position;
    Position diff;

    intended_position = get_intended_position(board_at(board, index), board->side_size);
    actual_position = position_from_index(index, board->side_size);
    diff = position_diff(intended_position, actual_position);

    return position_vector_length(diff);
}

int_signed get_all_points_distance(const Board* board)
{
    int_signed  total_distance;
    byte        index;
    byte        total_size;

    index = 0;
    total_distance = 0;
    total_size = board_get_total_size(board);

    while (index < total_size)
    {
        total_distance = get_manhattan_distnace(board, index);
        index ++;
    }

    return total_distance;
}

int_signed get_manhattan_distance_of_zero(const Board* board)
{
    return get_manhattan_distnace(board, board->empty_position_index);
}

int_signed get_manhattan_distance_of_zeroN(const Board* board)
{
    return -get_manhattan_distance_of_zero(board);
}
