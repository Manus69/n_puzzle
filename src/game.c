#include "game.h"
#include "declarations.h"
#include "definitions.h"
#include "why_lib.h"
#include "board_inline.h"
#include "board.h"

#include <assert.h>

static int_unsigned _estimate_table_capacity(int_signed total_size)
{
    return total_size * total_size * total_size * total_size;
}

Game* game_create(byte* values, int_signed total_size, int_signed (*metric)(const Board *))
{
    Game*           game;
    int_unsigned    capacity;

    game = allocate(sizeof(Game));

    capacity = _estimate_table_capacity(total_size);
    game->boards = hash_table_create(copy_shallow, board_destroy, hash_board, capacity);
    game->visited_boards = hash_table_create(copy_shallow, NULL, hash_board, capacity);
    game->queue = heap_create(copy_shallow, NULL, board_compare_metric_vals);
    game->metric = metric;
    game->metric_increment = (metric == metric_mhtn_all) ? metric_mhtn_after_swap : NULL; //

    game->current_board = board_create(values, total_size);
    if (check_parity(game->current_board))
        assert(0);
    board_register(game, game->current_board);
    
    board_compute_metric(game->current_board, game->metric);

    game->BOARD_TOTAL_SIZE = total_size;
    game->BOARD_SIDE_SIZE = math_is_perfect_square(total_size);
    game->solved_board = get_solved_board(total_size);

    return game;
}

void game_destroy(Game* game)
{
    hash_table_destroy(game->visited_boards);
    heap_destroy(game->queue);
    hash_table_destroy(game->boards);
    board_destroy(game->solved_board);
    free(game);
}

