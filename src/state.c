#include "why_lib.h"
#include "state.h"
#include "game.h"
#include "declarations.h"
#include "definitions.h"

static int_unsigned _estimate_used_board_count()
{
    return game_get_hash_table_capacity(_game);
}

State* state_create(byte* values)
{
    State*          state;
    int_unsigned    capacity;

    state = allocate(sizeof(State));
    capacity = _estimate_used_board_count();

    state->current_board = board_create_register(values);
    state->queue = heap_create(copy_shallow, NULL, metric_manhattan);
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