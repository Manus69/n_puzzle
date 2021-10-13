#include "board.h"
#include "game.h"
#include "definitions.h"
#include "declarations.h"
#include "why_lib.h"

#include <assert.h>

static byte _find_empty_position(byte* values)
{
    byte n;

    n = 0;
    while (n < _game->BOARD_SIDE_SIZE)
    {
        if (values[n] == EMPTY_CELL_VALUE)
            return n;
        
        n ++;
    }

    assert(0);
}

void board_init(Board* board, byte* values)
{
    board->values = (byte *)board + sizeof(Board);
    board->values = memory_init(board->values, values, _game->BOARD_TOTAL_SIZE);
    board->empty_position_index = _find_empty_position(values);
    board->hash_value = hash_board(board);
}

int_signed _get_board_mem_size()
{
    return sizeof(Board) + (_game->BOARD_TOTAL_SIZE * sizeof(byte));
}

Board* board_create(byte* values)
{
    Board*      board;
    int_signed  total_size;

    total_size = _get_board_mem_size();
    board = allocate(total_size);

    board_init(board, values);

    hash_table_insert_hashed(_game->boards, board, board_compare, board->hash_value);

    return board;
}

void board_destroy(Board* board)
{
    free(board);
}
