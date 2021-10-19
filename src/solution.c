#include "why_lib.h"
#include "declarations.h"
#include "board.h"

Array* get_solution(const Game* game, const Board* final_board)
{
    Array*      path;
    Board*      current;
    int_signed  capacity;

    capacity = game_get_visited_board_count(game);
    path = array_create_with_capacity(copy_shallow, NULL, capacity);
    current = (Board *)final_board;

    while (current->previous)
    {
        array_push_front(path, current);
        current = current->previous;
    }
    array_push_front(path, current);

    return path;
}