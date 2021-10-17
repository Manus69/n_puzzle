#include "board.h"
#include "board_inline.h"
#include "state.h"
#include "game.h"
#include "declarations.h"
#include "why_lib.h"

#include <stdio.h>

static int _compute_cell_width(int total_size)
{
    return (byte)math_log10(total_size);
}

static void _print_value(byte value, int cell_width)
{
    String* string;
    char*   characters;

    if (value)
    {
        string = convert_to_string_uint(value);
        characters = string_get_characters(string);
        printf("%*s", cell_width + 1, characters);
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
    Position    position;
    byte        value;

    if (!board)
        return ;
    
    position = (Position){0, 0};
    while (position.row < board->side_size)
    {
        position.col = 0;
        while (position.col < board->side_size)
        {
            value = board_at_position(board, position);
            _print_value(value, _compute_cell_width(board->side_size * board->side_size));
            position.col ++;
        }
        printf("\n");
        position.row ++;
    }
    printf("\n");
}

void print_current_board(const Game* game)
{
    Board* board;

    board = game->current_board;
    print_board(board);
}