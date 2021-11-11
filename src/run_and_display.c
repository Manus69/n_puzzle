#include "why_lib.h"
#include "declarations.h"
#include "game.h"
#include "board_inline.h"
#include "position_inline.h"
#include "why_hash_table_diagnostics.h"

#include <time.h>
#include <stdio.h>

// #define DBG

static void _display_solution(const Game* game)
{
    Array*      path;
    int_signed  n;

    path = get_solution(game, game->current_board);
    print_board(array_at(path, 0));
    n = 1;

    while (n < array_size(path))
    {
        print_arrow_downT();
        print_board(array_at(path, n));
        n ++;
    }

    array_destroy(path);
}

static void _display_last(const Game* game)
{
    print_board(game->initial_board);
    print_arrow_down();
    print_board(game->current_board);
}

static void _display_time(const Game* game, clock_t start)
{
    clock_t time;

    time = clock();
    printf("Time spent bootstrapping:       %f s. \n", time_diff(start, game->time_of_creation));
    printf("Time spent solving the puzzle:  %f s.\n", time_diff(game->time_of_creation, time));
}

static void _display_total_size(const Game* game)
{
    printf("Total number of nodes created:  %lld\n", game_get_number_of_boards(game));
}

static void _display_queue_size(const Game* game)
{
    printf("Number of nodes in queue:       %lld\n", game_get_queue_size(game));
}

static void _display_solution_size(const Game* game)
{
    Array* path;

    path = get_solution(game, game->current_board);
    printf("Path length from initial state: %lld\n", array_size(path));

    array_destroy(path);
}

static void _display_visited_size(const Game* game)
{
    printf("Number of visited nodes:        %lld\n", game_get_visited_board_count(game));
}

void _display_initial_state(const Game* game)
{
    int_signed number_of_transpositions;
    int_signed distance_from_zero;

    number_of_transpositions = count_transpositions(game->initial_board);
    distance_from_zero = metric_mhtn_zero(game->initial_board);

    printf("--------------\n");
    printf("Initial state:\n");
    print_board(game->initial_board);
    printf("Number of transpositions:       %lld\n", number_of_transpositions);
    printf("Distance from empty cell:       %lld\n", distance_from_zero);
    printf("--------------\n");
}

void _display_run_time(clock_t start, clock_t end)
{
    printf("Total time elapsed:             %f s\n", time_diff(start, end));
}

void _display_failure(const Game* game)
{
    printf("Iteration cap reached; Terminating\n");
    _display_total_size(game);
    _display_visited_size(game);
}

void run(Game* game, const Config* config, clock_t start)
{
    #ifdef DBG
        print_board(game->initial_board);
        // printf("\n");
    #endif

    if (check_parity(game->initial_board))
    {
        _display_initial_state(game);
        return ;
    }
    
    game_play(game);

    if (config_initial(config))
        _display_initial_state(game);

    if (config_all_boards(config))
        _display_solution(game);

    if (config_last_board(config))
        _display_last(game);

    if (config_created(config))
        _display_total_size(game);

    if (config_queue(config))
        _display_queue_size(game);
    
    if (config_visied(config))
        _display_visited_size(game);

    if (config_path_length(config))
        _display_solution_size(game);

    if (config_time(config))
        _display_time(game, start);
}