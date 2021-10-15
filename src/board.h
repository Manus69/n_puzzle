#ifndef BOARD_H
#define BOARD_H

#include "why_definitions.h"
#include "definitions.h"
#include "position.h"

struct Board
{
    Board*          previous;
    byte*           values;
    int_unsigned    hash_value;
    byte            empty_position_index;
    byte            side_size;
};

#define BOARD_SWAP(board, l_index, r_index) SWAP(board->values[l_index], board->values[r_index], byte)

static inline byte* board_get_values(const Board* board)
{
    return (byte *)board + sizeof(Board);
}

static inline byte board_get_total_size(const Board* board)
{
    return board->side_size * board->side_size;
}

static inline int_signed _get_board_mem_size(byte n_cells)
{
    return sizeof(Board) + (n_cells * sizeof(byte));
}

static inline byte board_at(const Board* board, byte n)
{
    return board->values[n];
}

static inline byte board_at_position(const Board* board, Position position)
{
    return board_at(board, index_from_position(position, board->side_size));
}

static inline byte board_get_index_of_zero(const Board* board)
{
    return board->empty_position_index;
}

static inline Position board_get_position_of_zero(const Board* board)
{
    return position_from_index(board->empty_position_index, board->side_size);
}

static inline void board_set_previous(Board* board, const Board* previous)
{
    board->previous = (Board *)previous;
}

// void board_swap(Board* board, byte l_index, byte r_index)
// {
//     SWAP(board->values[l_index], board->values[r_index], unsigned char);
// }

#endif