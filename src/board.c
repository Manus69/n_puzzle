#include "board.h"
#include "definitions.h"
#include "declarations.h"
#include "why_lib.h"
#include "position.h"
// #include "inline_declarations.h"

#include <assert.h>

static byte _find_empty_position(byte* values, byte n_cells)
{
    byte n;

    n = 0;
    while (n < n_cells)
    {
        if (values[n] == EMPTY_CELL_VALUE)
            return n;
        
        n ++;
    }

    assert(0);
}

void board_init(Board* board, byte* values, byte n_cells)
{
    board->values = board_get_values(board);
    board->values = memory_init(board->values, values, n_cells);
    board->empty_position_index = _find_empty_position(values, n_cells);
    board->side_size = math_is_perfect_square(n_cells);
    board->previous = NULL;
    board->hash_value = hash_board(board);
}

void board_init_fields(Board* board, const Board* previous, byte ep_index)
{
    board->values = board_get_values(board);
    board->empty_position_index = ep_index;
    board->previous = (Board *)previous;
    board->hash_value = hash_board(board);
}

Board* board_create(byte* values, byte n_cells)
{
    Board*      board;
    int_signed  mem_size;

    mem_size = _get_board_mem_size(n_cells);
    board = allocate(mem_size);

    board_init(board, values, n_cells);

    return board;
}

Board* board_copy(const Board* board)
{
    Board* new_board;

    new_board = memory_copy(board, _get_board_mem_size(board->side_size * board->side_size));
    new_board->values = board_get_values(new_board);

    return new_board;
}

void board_destroy(Board* board)
{
    free(board);
}

