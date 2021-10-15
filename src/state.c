#include "why_lib.h"
#include "state.h"
#include "game.h"
#include "declarations.h"
#include "definitions.h"

static int_unsigned _estimate_used_board_count(const Game* game)
{
    return game_get_hash_table_capacity(game);
}

State* state_create(byte* values, const Game* game)
{
    State*          state;
    int_unsigned    capacity;

    state = allocate(sizeof(State));
    capacity = _estimate_used_board_count(game);
    state->queue_compare_function = board_compare_manhattan_zero;
    state->metric = get_manhattan_distance_of_zeroN;

    state->current_board = board_create_register(values, game->BOARD_TOTAL_SIZE);
    state->metric_value = state->metric(state->current_board);

    state->queue = heap_create_with_capacity(copy_shallow, NULL, state->queue_compare_function, 32); //
    state->used_boards = hash_table_create(copy_shallow, NULL, hash_board, capacity);

    return state;
}

void state_destroy(State* state)
{
    // board_destroy(state->current_board);
    heap_destroy(state->queue);
    hash_table_destroy(state->used_boards);
    free(state);
}