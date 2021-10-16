#include "game.h"
#include "board_inline.h"
#include "declarations.h"
#include "why_lib.h"

#include <assert.h>

int_signed game_get_number_of_boards(const Game* game)
{
    return hash_table_number_of_items(game->boards);
}

int_unsigned game_get_hash_table_capacity(const Game* game)
{
    return hash_table_capacity(game->boards);
}

int_signed game_get_queue_size(const Game* game)
{
    return heap_size(game->queue);
}

int_signed game_get_visited_board_count(const Game* game)
{
    return hash_table_number_of_items(game->visited_boards);
}

bool board_register(Game* game, const Board* board)
{
    return hash_table_insert_hashed(game->boards, board, board_compare_values, board->hash_value);
}

bool board_exists(Game* game, const Board* board)
{
    return hash_table_is_in_hashed(game->boards, board, board_compare_values, board->hash_value);
}
