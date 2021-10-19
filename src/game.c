#include "game.h"
#include "declarations.h"
#include "definitions.h"
#include "why_lib.h"
#include "board_inline.h"
#include "board.h"

#include <assert.h>

#define H_TABLE_SIZE9 1000
#define H_TABLE_SIZE16 100000
#define H_TABLE_SIZE25 300000

static int_unsigned _estimate_table_capacity(int_signed total_size)
{
    if (total_size == 9)
        return H_TABLE_SIZE9;
    else if (total_size == 16)
        return H_TABLE_SIZE16;
    // else if (total_size == 25)
    //     return H_TABLE_SIZE25;
    
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
    game->metric_increment = (metric == metric_mhtn) ? metric_mhtn_after_swap : NULL; //

    game->current_board = board_create(values, total_size);

    board_register(game, game->current_board);
    board_compute_metric(game->current_board, game->metric);

    game->BOARD_TOTAL_SIZE = total_size;
    game->BOARD_SIDE_SIZE = math_is_perfect_square(total_size);
    game->solved_board = get_solved_board(total_size);
    game->initial_board = game->current_board;
    game->time_of_creation = clock();

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

