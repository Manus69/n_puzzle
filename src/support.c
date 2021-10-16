#include "why_lib.h"
#include "game.h"
#include "definitions.h"
#include "declarations.h"
#include "board.h"
#include "board_inline.h"

#include <assert.h>

// #define DBG

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

    while (n < total_size - 1)
    {
        while ((value = board_at(scratch_board, n)) != n + 1)
        {
            board_swap(scratch_board, n, value - 1);

            swaps ++;
        }

        n ++;
    }

    #ifdef DBG
        print_board(scratch_board);
    #endif

    board_destroy(scratch_board);
    
    return swaps;
}

byte check_parity(const Board* board)
{
    Board*      scratch_board;
    int_signed  total_size;

    total_size = board_get_total_size(board);
    scratch_board = board_copy(board);
    board_swap(scratch_board, board->empty_position_index, total_size - 1);

    return count_transpositions(scratch_board) % 2; 
}

Board* get_solved_board(int_signed total_size)
{
    byte values[total_size];
    byte n;

    n = 0;
    while (n < total_size)
    {
        values[n] = n + 1;
        n ++;
    }

    values[n - 1] = 0;

    return board_create(values, total_size);
}
