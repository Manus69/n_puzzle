#include "why_lib.h"
#include "declarations.h"
#include "game.h"

#include <time.h>
#include <stdio.h>

void _at_exit()
{
    get_line(-1);
    game_destroy(_game);
}

void test()
{
    Array*  strings;
    byte*   bytes;
    State*  state;

    strings = string_splitCSTR("1 0 2 3 4 5 6 7 8", ' ');
    // print_array(strings, print_string, "\n");
    bytes = input_get_bytes(strings);
    _game = game_create(array_size(strings));
    state = state_create(bytes);
    print_current_board(state);

    state_destroy(state);
    array_destroy(strings);
    free(bytes);
}

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    atexit(_at_exit);

    test();

    end = clock();

    printf("Time elapsed: %f s\n", (end - start) / (double) CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}