#include "game.h"
#include "board_inline.h"
#include "why_lib.h"
#include "declarations.h"

int_signed _game_compute_invariant(const Game* game)
{
    int_signed boards_created;
    int_signed boards_in_queue;
    int_signed boards_visited;

    boards_created = game_get_number_of_boards(game);
    boards_in_queue = game_get_queue_size(game);
    boards_visited = game_get_visited_board_count(game);

    return boards_created - (boards_in_queue + boards_visited);
}