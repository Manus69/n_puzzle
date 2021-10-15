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
            _print_value(value);
            position.col ++;
        }
        printf("\n");
        position.row ++;
    }
    printf("\n");
}

void print_current_board(const State* state)
{
    Board* board;

    board = state->current_board;
    print_board(board);
}