
#include "why_lib.h"
#include "game.h"
#include "game.h"
#include "board.h"
#include "board_inline.h"
#include "declarations.h"
#include "definitions.h"
#include "game_diagnostics.h"

#include <assert.h>
#include <stdio.h>

#define _SIZE 4

// #define CURRENT_DBG
// #define QUEUE_DBG
// #define INVARIANT_DBG
// #define ITERATION_COUNT_DBG
// #define CMP_DBG

static const void* _functions[] = {board_down, board_right, board_up, board_left, 0};

bool game_is_solvedM(const Game* game)
{
    return game->current_board->metric_value == 0;
}

bool game_is_solved(const Game* game)
{
    #ifdef CMP_DBG
        if (game->current_board->hash_value % 661 == 125)
        {
            printf("Comparing:\n");
            print_board(game->current_board);
            int_signed value = board_compare_values(game->solved_board, game->current_board);
            printf("comparison: %lld\n", value);
        }
    #endif

    if (board_compare_hash(game->solved_board, game->current_board) != 0)
        return false;

    return board_compare_values(game->solved_board, game->current_board) == 0;
}

bool game_add_to_queue(Game* game, const Board* item)
{
    return heap_push(game->queue, item);
}

bool game_board_is_visited(const Game* game, const Board* board)
{
    if (!board)
        return true;
    
    return hash_table_is_in_hashed(game->visited_boards, board, board_compare_values, board->hash_value);
}

bool game_mark_current_as_visited(Game* game)
{
    return hash_table_insert_hashed(game->visited_boards, game->current_board, board_compare_values, game->current_board->hash_value);
}

Board* game_get_next_board(Game* game)
{
    Board* next_board;

    while (true)
    {
        if (!(next_board = heap_pop_root(game->queue)))
            return NULL;
        
        if (game_board_is_visited(game, next_board))
            continue ;

        return next_board;
    }
}

static void _process_new_board(Game* game, Board* new_board)
{
    if (!new_board)
        return ;

    if (board_exists(game, new_board))
        return board_destroy(new_board);

    // if (game_board_is_visited(game, new_board))
    //     return board_destroy(new_board);
    
    // board_compute_metric(new_board, game->metric);
    board_register(game, new_board);

    #ifdef QUEUE_DBG
        printf("####\nadding board with value %lld to queue:\n", game->metric(new_board));
        print_board(new_board);
    #endif

    game_add_to_queue(game, new_board);

    #ifdef QUEUE_DBG
        printf("----\nheap state:\n");
        print_heap(game->queue, print_board);
        printf("----------\n");
    #endif
}

static void _process_neighbours(Game* game)
{
    Board*      (*move_function)();
    Board*      new_board;
    int_signed  n;

    n = 0;
    while (n < _SIZE)
    {
        move_function = _functions[n];
        new_board = move_function(game, game->current_board);

        _process_new_board(game, new_board);

        n ++;
    }
}

bool game_process_current_board(Game* game)
{
    if (game_is_solved(game))
        return true;

    if (game->current_board == NULL)
        assert(0);

    if (game_board_is_visited(game, game->current_board))
        assert(0);

    _process_neighbours(game);
    game_mark_current_as_visited(game);

    game->current_board = game_get_next_board(game);

    #ifdef CURRENT_DBG
        printf("@@@@@@\ncurrent board:\n");
        print_board(game->current_board);
    #endif

    return false;
}

Board* game_play(Game* game)
{
    int_signed invariant;

    #ifdef ITERATION_COUNT_DBG
        int_signed n_iterations = 0;
        int_signed cap = (1 << 20);
    #endif

    while (!game_process_current_board(game))
    {
        // print_board(game->current_board);
        invariant = _game_compute_invariant(game);

        if (invariant != 1)
        {
            printf("Invariant condition is violated;\n");
            return NULL;
        }
        
        #ifdef ITERATION_COUNT_DBG
            if ((n_iterations ++) == cap)
            {
                printf("Iteration cap reached\n");
                return NULL;
            }
        #endif

        #ifdef INVARIANT_DBG
            printf("INVARIANT = %lld\n", _game_compute_invariant(game));
        #endif 
    }
    
    return game->current_board;
}