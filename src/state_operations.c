#include "why_lib.h"
#include "state.h"
#include "game.h"
#include "board.h"
#include "declarations.h"
#include "definitions.h"

#include <assert.h>
#include <stdio.h>

#define _SIZE 4

#define CURRENT_DBG
#define QUEUE_DBG

static const void* _functions[] = {board_up, board_down, board_left, board_right, 0};

bool state_check_if_solved(const State* state)
{
    return board_compare_hash(state->current_board, _game->solved_board) == 0;
}

bool state_add_to_queue(State* state, const Board* item)
{
    return heap_push(state->queue, item);
}

bool state_board_visited(const State* state, const Board* board)
{
    if (!board)
        return true;
    
    return hash_table_is_in_hashed(state->used_boards, board, board_compare_values, board->hash_value);
}

bool state_mark_current_as_visited(State* state)
{
    return hash_table_insert_hashed(state->used_boards, state->current_board, board_compare_values, state->current_board->hash_value);
}

Board* state_get_next_board(State* state)
{
    Board* next_board;

    while (true)
    {
        if (!(next_board = heap_pop_root(state->queue)))
            return NULL;
        
        if (state_board_visited(state, next_board))
            continue ;

        return next_board;
    }
}

static void _process_new_board(State* state, Board* new_board)
{
    if (!new_board)
        return ;

    if (state_board_visited(state, new_board))
        return board_destroy(new_board);
    
    board_register(new_board);

    #ifdef QUEUE_DBG
        printf("####\nadding board with value %lld to queue:\n", state->metric(new_board));
        print_board(new_board);
    #endif

    state_add_to_queue(state, new_board);

    #ifdef QUEUE_DBG
        printf("----\nheap state:\n");
        print_heap(state->queue, print_board);
        printf("----------\n");
    #endif
}

static void _process_neighbours(State* state)
{
    Board*      (*move_function)();
    Board*      new_board;
    int_signed  n;

    n = 0;
    while (n < _SIZE)
    {
        move_function = _functions[n];
        new_board = move_function(state->current_board);

        _process_new_board(state, new_board);

        n ++;
    }
}

bool state_process_current_board(State* state)
{
    if (state_check_if_solved(state))
        return true;

    if (state->current_board == NULL)
        assert(0);

    if (state_board_visited(state, state->current_board))
        assert(0);

    _process_neighbours(state);
    state_mark_current_as_visited(state);

    state->current_board = state_get_next_board(state);
    state->metric_value = state->metric(state->current_board);

    #ifdef CURRENT_DBG
        printf("@@@@@@\ncurrent board:\n");
        print_board(state->current_board);
    #endif

    return false;
}

Board* state_solve(State* state)
{
    while (!state_process_current_board(state))
        ;
    
    return state->current_board;
}