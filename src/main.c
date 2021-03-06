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
#include <assert.h>

void _at_exit()
{
    get_line(-1);
}

void hash_test()
{
    Board* lhs;
    Board* rhs;


    lhs = board_create(input_get_bytesCSTR("1 2 3 4 5 6 7 8 0"), 9);
    rhs = get_solved_board(9);

    printf("lhs hash = %llu\nrhs hash = %llu\n%lld\n",
    lhs->hash_value, rhs->hash_value, lhs->hash_value % 661);

    board_destroy(lhs);
    board_destroy(rhs);
}

void metric_test()
{
    Board* board;
    int_signed metric;


    board = board_create(input_get_bytesCSTR("1 6 2 0 4 3 7 8 5 "), 9);
    print_board(board);
    metric = metric_mhtn(board);

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

    7 2 4 
    8 6 1 
    0 5 3

*/

const char* solvable[] =
{"1 2 3 6 4 5 7 0 8", //0
"1 2 3 4 7 6 8 5 0", //1
"1 2 3 4 5 6 7 0 8", //2 4 1 2 ; 0
"1 2 3 4 5 6 7 8 0", //3 1 0 0 ; 0
"1 2 6 4 5 3 8 7 0", //4
"1 2 6 5 7 3 8 4 0", //5
"2 7 4 5 1 6 8 3 0", //6
"5 7 6 1 0 2 4 8 3", //7 asserts
"7 2 4 8 6 1 0 5 3", //8 takes forever and asserts
"2 4 7 8 1 6 0 5 3", //9 
"1 2 3 5 8 6 7 4 0", //10
"3 8 6 7 2 4 1 5 0", //11
}; 

const char* unsolvable[] = 
{"2 1 3 8 0 4 7 6 5",
"3 1 8 5 4 7 2 6 0 ",
"4 6 0 1 8 7 2 3 5 ",
"4  9 15 14 12  6  1  3 13  0  7  2  8  5 11 10 ",};

// #define DISTRIBUTION

// void test()
// {
//     Board*  solution;
//     Game*   game;

//     // game = get_game_from_file("test.txt", metric_mhtn);
//     solution = game_play(game);

//     Array* path = get_solution(game, solution);
//     print_array(path, print_board, NULL);
//     printf("Path lenght: %lld\n", array_size(path));

//     display_status(game);

//     #ifdef DISTRIBUTION
//         Array* distr = _hash_table_get_distribution(game->boards);
//         print_distribution(distr);
//         array_destroy(distr);
//     #endif

//     array_destroy(path);
//     // array_destroy(strings);
//     game_destroy(game);
//     // free(bytes);
// }


//capacity computation
//includes (dont include more than you need)
//author file
//check if inlinig affects performance
//display hash table distribution
//uniform metric does not solve
//misplaced metric is weird

int main(int argc, char** argv)
{
    clock_t     start;
    Game*       game;
    Config*     config;

    start = clock();
    atexit(_at_exit);

    if (!(config = config_create()))
    {
        error_display();
        return EXIT_FAILURE;
    }

    if (argc == 1)
        game = get_game_from_stdin(config);
    else if (argc == 2)
        game = get_game_from_file(argv[1], config);
    else
    {
        display_usage();
        return EXIT_SUCCESS;
    }

    if (!game)
        assert(0);

    // metric_test();
    // hash_test();
    
    run(game, config, start);
    game_destroy(game);
    config_destroy(config);

    _display_run_time(start, clock());

    return EXIT_SUCCESS;
}