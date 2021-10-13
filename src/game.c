#include "game.h"
#include "declarations.h"

#include <assert.h>

Game* _game;

static int_unsigned _estimate_table_capacity(int_signed total_size)
{
    return total_size * total_size;
}

Game* game_create(int_signed total_size)
{
    Game*           game;
    int_unsigned    capacity;

    game = allocate(sizeof(Game));
    game->BOARD_TOTAL_SIZE = total_size;
    game->BOARD_SIDE_SIZE = math_is_perfect_square(total_size);

    if (game->BOARD_SIDE_SIZE == 0)
        assert(0);
    
    capacity = _estimate_table_capacity(total_size);
    game->boards = hash_table_create(copy_shallow, board_destroy, hash_board, capacity);

    return game;
}

void game_destroy(Game* game)
{
    hash_table_destroy(game->boards);
    free(game);
}

int_unsigned game_get_hash_table_capacity(const Game* game)
{
    return hash_table_capacity(game->boards);
}