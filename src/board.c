#include "board.h"
#include "game.h"
#include "definitions.h"
#include "declarations.h"
#include "why_lib.h"

#include <assert.h>

static byte _find_empty_position(byte* values, int_signed size)
{
    byte n;

    n = 0;
    while (n < size)
    {
        if (values[n] == EMPTY_CELL_VALUE)
            return n;
        
        n ++;
    }

    assert(0);
}

byte* _board_get_values_pointer(const Board* board)
{
    return (byte *)board + sizeof(Board);
}

void board_init_size(Board* board, byte* values, int_signed size)
{
    board->values = _board_get_values_pointer(board);
    board->values = memory_init(board->values, values, size);
    board->empty_position_index = _find_empty_position(values, size);
    board->hash_value = hash_board_size(board, size);
    board->previous = NULL;
}

void board_init(Board* board, byte* values)
{
    return board_init_size(board, values, _game->BOARD_TOTAL_SIZE);
}

int_signed _get_board_mem_size()
{
    return sizeof(Board) + (_game->BOARD_TOTAL_SIZE * sizeof(byte));
}

static int_signed _get_board_mem_sizeBSTRP(int_signed size)
{
    return sizeof(Board) + (size * sizeof(byte));
}

Board* board_create_size(byte* values, int_signed size)
{
    Board*      board;
    int_signed  total_size;

    total_size = _get_board_mem_sizeBSTRP(size);
    board = allocate(total_size);

    board_init_size(board, values, size);

    return board;
}

Board* board_create(byte* values)
{
    return board_create_size(values, _game->BOARD_TOTAL_SIZE);
}

Board* board_create_register(byte* values)
{
    Board* board;

    board = board_create(values);
    board_register(board);

    return board;
}

Board* board_copy(const Board* board)
{
    Board* new_board;

    new_board = memory_copy(board, _get_board_mem_size());
    new_board->values = _board_get_values_pointer(new_board);

    return new_board;
}

bool board_register(const Board* board)
{
    return hash_table_insert_hashed(_game->boards, board, board_compare_values, board->hash_value);
}

bool board_exists(const Board* board)
{
    return hash_table_is_in_hashed(_game->boards, board, board_compare, board->hash_value);
}

void board_destroy(Board* board)
{
    free(board);
}

void board_set_previous(Board* board, const Board* previous)
{
    board->previous = (Board *)previous;
}