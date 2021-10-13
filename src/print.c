#include "board.h"
#include "state.h"
#include "game.h"
#include "declarations.h"

#include <stdio.h>

static void _print_value(byte value)
{
    String* string;
    char*   characters;

    if (value)
    {
        string = convert_to_string_uint(value);
        characters = string_get_characters(string);
        printf("%.*s", _game->CELL_SIZE + 1, characters);
        string_destroy(string);
    }
    else 
    {
        printf("_");
    }
    printf(" ");
}

void print_board(const Board* board)
{
    int_signed  j;
    int_signed  k;
    byte        value;

    if (!board)
        return ;
    
    j = 0;
    while (j < _game->BOARD_SIDE_SIZE)
    {
        k = 0;
        while (k < _game->BOARD_SIDE_SIZE)
        {
            value = board_atG(board, j, k);
            _print_value(value);
            k ++;
        }
        printf("\n");
        j ++;
    }
    printf("\n");
}

void print_current_board(const State* state)
{
    Board* board;

    board = state->current_board;
    print_board(board);
}