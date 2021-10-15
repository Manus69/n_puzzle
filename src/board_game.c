#include "board.h"
#include "game.h"
#include "definitions.h"
#include "declarations.h"
#include "why_lib.h"
#include "position.h"
// #include "inline_declarations.h"

#include <assert.h>

Board* board_create_register(byte* values, byte n_cells)
{
    Board* board;

    board = board_create(values, n_cells);
    board_register(board);

    return board;
}

bool board_register(const Board* board)
{
    return hash_table_insert_hashed(_game->boards, board, board_compare_values, board->hash_value);
}

bool board_exists(const Board* board)
{
    return hash_table_is_in_hashed(_game->boards, board, board_compare_values, board->hash_value);
}