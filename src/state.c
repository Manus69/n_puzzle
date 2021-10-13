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

    state->current_board = board_create(values);
    state->queue = heap_create(copy_shallow, NULL, board_compare); //this needs a proper metric
    state->used_boards = hash_table_create(copy_shallow, NULL, hash_board, capacity);
    state->path = array_create(copy_shallow, NULL);

    return state;
}

void state_destroy(State* state)
{
    heap_destroy(state->queue);
    hash_table_destroy(state->used_boards);
    array_destroy(state->path);
    free(state);
}