#include "board.h"

#include <assert.h>

static byte _find_empty_position(byte* values)
{
    byte n;

    n = 0;
    while (n < BOARD_SIZE)
    {
        if (values[n] == EMPTY_CELL_VALUE)
            return n;
        
        n ++;
    }

    assert(0);
}

byte c_map(byte row, byte col)
{
    return row * col + col;
}

byte c_row(byte index)
{
    return index / BOARD_SIZE;
}

byte c_col(byte index)
{
    return index % BOARD_SIZE;
}

void board_init(Board* board, byte* values)
{
    board->values = memory_init(board->values, values, BOARD_SIZE);
    board->empty_position_index = _find_empty_position(values);
}

Board* board_create(byte* values)
{
    Board* board;

    board = allocate(sizeof(Board) + sizeof(byte *) + sizeof(byte) + BOARD_SIZE * sizeof(byte));
    board->empty_position_index = (byte *)board + sizeof(Board);
    board->values = board->empty_position_index + sizeof(byte);

    board_init(board, values);

    return board;
}

byte board_at(const Board* board, byte n)
{
    return board->values[n];
}

byte board_atG(const Board* board, byte row, byte col)
{
    return board_at(board, c_map(row, col));
}
