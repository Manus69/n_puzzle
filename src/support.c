#include "why_lib.h"
#include "game.h"
#include "definitions.h"
#include "declarations.h"
#include "board.h"

#include <assert.h>

int_signed count_transpositions(const Board* board)
{
    int_signed  swaps;
    int_signed  n;
    byte        value;
    byte        total_size;
    Board*      scratch_board;

    swaps = 0;
    n = 0;
    scratch_board = board_copy(board);
    total_size = board_get_total_size(board);

    while (n < total_size)
    {
        // value = board_at(board, n);
        while ((value = board_at(board, n)) != n + 1)
        {
            BOARD_SWAP(scratch_board, n, value);
            swaps ++;
        }

        n ++;
    }

    board_destroy(scratch_board);
    
    return swaps;
}