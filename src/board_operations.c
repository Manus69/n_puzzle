#include "board.h"
#include "game.h"
#include "definitions.h"
#include "declarations.h"
#include "why_lib.h"

#include <assert.h>

byte map_to_index(byte row, byte col)
{
    return row * col + col;
}

byte map_to_row(byte index)
{
    return index / _game->BOARD_SIDE_SIZE;
}

byte map_to_col(byte index)
{
    return index % _game->BOARD_SIDE_SIZE;
}

short index_above(byte index)
{
    return (short)index - _game->BOARD_SIDE_SIZE;
}

short index_below(byte index)
{
    return (short)index + _game->BOARD_SIDE_SIZE;
}

short index_leftward(byte index)
{
    return index % _game->BOARD_SIDE_SIZE == 0 ? -1 : index - 1;
}

short index_rightward(byte index)
{
    return index % _game->BOARD_SIDE_SIZE == _game->BOARD_SIDE_SIZE - 1 ? -1 : index + 1;
}

static bool _index_in_range(short index)
{
    return (index > 0) && (index < _game->BOARD_TOTAL_SIZE);
}

byte board_at(const Board* board, byte n)
{
    return board->values[n];
}

byte board_atG(const Board* board, byte row, byte col)
{
    return board_at(board, map_to_index(row, col));
}

static void _swap(Board* board, byte l_index, byte r_index)
{
    SWAP(board->values[l_index], board->values[r_index], byte);
}

int_signed board_compare(const Board* lhs, const Board* rhs)
{
    int_signed n;

    n = 0;
    while (n < _game->BOARD_TOTAL_SIZE)
    {
        if (lhs->values[n] != rhs->values[n])
            break ;
        n ++;
    }

    return n == _game->BOARD_TOTAL_SIZE ? 0 : rhs->values[n] - lhs->values[n];
}

static Board* _board_move(const Board* board, short (*index_function)(byte))
{
    Board*  new_board;
    short   index;

    index = index_function(board->empty_position_index);
    if (!_index_in_range(index))
        return NULL;
    
    new_board = memory_copy(board, _get_board_mem_size());
    _swap(new_board, index, board->empty_position_index);
    new_board->empty_position_index = index;
    new_board->hash_value = hash_board(new_board);

    hash_table_insert_hashed(_game->boards, new_board, board_compare, new_board->hash_value);

    return new_board;
}

Board* board_up(const Board* board)
{
    return _board_move(board, index_above);
}

Board* board_down(const Board* board)
{
    return _board_move(board, index_below);
}

Board* board_left(const Board* board)
{
    return _board_move(board, index_leftward);
}

Board* board_right(const Board* board)
{
    return _board_move(board, index_rightward);
}