#include "board.h"
#include "position.h"
#include "declarations.h"

byte* board_get_values(const Board* board)
{
    return (byte *)board + sizeof(Board);
}

byte board_get_total_size(const Board* board)
{
    return board->side_size * board->side_size;
}

byte board_get_side_size(const Board* board)
{
    return board->side_size;
}

int_signed _get_board_mem_size(byte n_cells)
{
    return sizeof(Board) + (n_cells * sizeof(byte));
}

byte board_at(const Board* board, byte n)
{
    return *(board_get_values(board) + n);
}

byte board_set(Board* board, byte value, byte index)
{
    byte old_value;

    old_value = board_at(board, index);
    *((byte *)board + sizeof(Board) + index) = value;

    return old_value;

}

byte board_at_position(const Board* board, Position position)
{
    return board_at(board, index_from_position(position, board->side_size));
}

byte board_get_index_of_zero(const Board* board)
{
    return board->empty_position_index;
}

Position board_get_position_of_zero(const Board* board)
{
    return position_from_index(board->empty_position_index, board->side_size);
}

void board_set_previous(Board* board, const Board* previous)
{
    board->previous = (Board *)previous;
}

void board_swap(Board* board, byte l_index, byte r_index)
{
    byte swap;

    swap = board_set(board, board_at(board, l_index), r_index);
    *((byte *)board + sizeof(Board) + l_index) = swap;
}

void board_compute_metric(Board* board, int_signed (*metric)(const Board*))
{
    board->metric_value = -metric(board);
}