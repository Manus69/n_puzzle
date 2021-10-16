#include "why_definitions.h"
#include "definitions.h"
#include "declarations.h"
#include "board.h"
#include "board_inline.h"
#include "game.h"
#include "position.h"

#include <stdlib.h>

static bool _board_move(Board* board, short (*index_function)(short, short))
{
    short   index;

    index = index_function(board->empty_position_index, board->side_size);
    if (!index_is_valid(index, board_get_total_size(board)))
        return false;

    board_swap(board, index, board->empty_position_index);

    return true;
}

bool _board_up(Board* board)
{
    return _board_move(board, index_above);
}

bool _board_down(Board* board)
{
    return _board_move(board, index_below);
}

bool _board_left(Board* board)
{
    return _board_move(board, index_leftward);
}

bool _board_right(Board* board)
{
    return _board_move(board, index_rightward);
}

static Board* _board_move_create(const Board* board, short (*index_function)(short, short))
{
    Board*  new_board;
    short   index;

    index = index_function(board->empty_position_index, board->side_size);
    if (!index_is_valid(index, board_get_total_size(board)))
        return NULL;
    
    new_board = board_copy(board);
    board_swap(new_board, index, board->empty_position_index);
    board_init_fields(new_board, board, index);

    return new_board;
}

Board* board_up(const Board* board)
{
    return _board_move_create(board, index_above);
}

Board* board_down(const Board* board)
{
    return _board_move_create(board, index_below);
}

Board* board_left(const Board* board)
{
    return _board_move_create(board, index_leftward);
}

Board* board_right(const Board* board)
{
    return _board_move_create(board, index_rightward);
}