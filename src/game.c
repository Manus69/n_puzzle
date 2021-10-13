#include "game.h"
#include "declarations.h"
#include "definitions.h"

#include <assert.h>

Game* _game;

static int_unsigned _estimate_table_capacity(int_signed total_size)
{
    return total_size * total_size;
}

static byte _get_cell_size(int_signed total_size)
{
    return (byte)math_log10(total_size);
}

static Board* _get_solved_board(int_signed total_size)
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

    return board_create_size(values, total_size);
}

Game* _game_create(int_signed total_size)
{
    Game*           game;

    game = allocate(sizeof(Game));
    game->BOARD_TOTAL_SIZE = total_size;
    game->BOARD_SIDE_SIZE = math_is_perfect_square(total_size);
    game->CELL_SIZE = _get_cell_size(total_size);

    if (game->BOARD_SIDE_SIZE == 0)
        assert(0);

    return game;
}

Game* game_create(int_signed total_size)
{
    Game*           game;
    int_unsigned    capacity;
    
    game = _game_create(total_size);
    capacity = _estimate_table_capacity(total_size);
    game->boards = hash_table_create(copy_shallow, board_destroy, hash_board, capacity);
    game->solved_board = _get_solved_board(total_size);

    return game;
}

void game_destroy(Game* game)
{
    hash_table_destroy(game->boards);
    board_destroy(game->solved_board);
    free(game);
}

int_unsigned game_get_hash_table_capacity(const Game* game)
{
    return hash_table_capacity(game->boards);
}