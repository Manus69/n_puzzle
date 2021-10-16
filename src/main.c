#include "why_lib.h"
#include "declarations.h"
#include "game.h"
#include "position.h"
#include "board_inline.h"
#include "position_inline.h"
#include "inline_declarations.h"
#include "why_hash_table_diagnostics.h"

#include <time.h>
#include <stdio.h>

void _at_exit()
{
    get_line(-1);
}

void metric_test()
{
    Board* board;
    int_signed metric;


    board = board_create(input_get_bytesCSTR("1 2 0 8 4 3 7 6 5"), 9);
    print_board(board);
    metric = metric_mhtn_all(board);

    print_intN(metric);
}

void display_status(const Game* game)
{
    printf("Boards created: %lld\n", game_get_number_of_boards(game));
    printf("Boards visited: %lld\n", game_get_visited_board_count(game));
    printf("Boards in queue: %lld\n", game_get_queue_size(game));
}

/*
    1 2 3
    4 5 6
    7 8 0

    2 1 3
    8 0 4
    7 6 5
*/

const char* solvable[] = {"1 2 3 4 0 5 7 8 6", "1 2 3 4 7 6 8 5 0", "1 2 3 4 5 6 7 0 8", "1 2 3 4 5 6 7 8 0", 
                            "1 2 3 8 4 0 7 6 5", "1 2 3 8 6 4 7 5 0"};
const char* unsolvable[] = {"2 1 3 8 0 4 7 6 5", "3 1 8 5 4 7 2 6 0 "};

void test()
{
    Array*  strings;
    byte*   bytes;
    Board*  solution;
    Game*   game;

    // strings = string_splitCSTR(solvable[1], ' ');
    strings = string_splitCSTR(unsolvable[0], ' ');
    // strings = string_splitCSTR("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15", ' ');
    bytes = input_get_bytes(strings);
    game = game_create(bytes, array_size(strings), metric_mhtn_all);
    // game = game_create(bytes, array_size(strings), metric_mhtn_zero);
    // print_board(game->solved_board);
    print_current_board(game);
    printf("//\n");

    // int_signed result = check_parity(game->current_board);
    // printf("%lld\n", result);

    solution = game_play(game);
    // print_board(solution);

    display_status(game);
    Array* distr = _hash_table_get_distribution(game->boards);
    print_distribution(distr);
    array_destroy(distr);

    array_destroy(strings);
    game_destroy(game);
    free(bytes);
}

//unfuck the includes (dont include more than you need)
//count transpositions
//memory leaks on some moves

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    atexit(_at_exit);

    test();
    // metric_test();

    end = clock();

    printf("Time elapsed: %f s\n", (end - start) / (double) CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}