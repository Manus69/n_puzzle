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
        value = board_at(scratch_board, n);
        if (value == 0)
        {
            board_swap(scratch_board, n, total_size - 1);
            swaps ++;
        }
        else if (value == n + 1)
            n ++;
        else
        {
            board_swap(scratch_board, n, value - 1);
            swaps ++;
        }
    }

    board_destroy(scratch_board);
    
    return swaps;
}

int_signed count_misplaced_elements(const Board* board)
{
    int_signed count;
    int_signed n;
    int_signed total_size;

    count = 0;
    n = 0;
    total_size = board_get_total_size(board);

    while (n < total_size)
    {
        if (!value_in_correct_position(board_at(board, n), n, board->side_size))
            count ++;
        
        n ++;
    }

    return count;
}

byte check_parity(const Board* board)
{
    int_signed  transpositions;
    byte        parity;
    int_signed  distance_from_zero;

    #ifdef DBG
        print_board(board);
    #endif

    transpositions = count_transpositions(board);
    distance_from_zero = metric_mhtn_zero(board);
    parity = (transpositions + distance_from_zero) % 2;

    return parity;
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

double time_diff(clock_t start, clock_t end)
{
    return (end - start) / (double) CLOCKS_PER_SEC;
}
