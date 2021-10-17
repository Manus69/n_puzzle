#include "why_lib.h"
#include "declarations.h"
#include "board.h"

Array* get_solution(const Board* final_board)
{
    Array* path;
    Board* current;

    path = array_create(copy_shallow, NULL);
    current = (Board *)final_board;
    while (current->previous)
    {
        array_push(path, current);
        current = current->previous;
    }
    array_push(path, current);

    return path;
}