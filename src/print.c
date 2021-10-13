#include "board.h"
#include "state.h"
#include "game.h"
#include "declarations.h"

#include <stdio.h>

void print_board(const Board* board)
{
    int_signed  j;
    int_signed  k;
    byte        value;
    String*     string;

    j = 0;
    while (j < _game->BOARD_SIDE_SIZE)
    {
        k = 0;
        while (k < _game->BOARD_SIDE_SIZE)
        {
            value = board_atG(board, j, k);
            string = convert_to_string_uint(value);
            print_string(string);
            printf(" ");
            string_destroy(string);
            k ++;
        }
        printf("\n");
        j ++;
    }
}

void print_current_board(const State* state)
{
    Board* board;

    board = state->current_board;
    print_board(board);
}