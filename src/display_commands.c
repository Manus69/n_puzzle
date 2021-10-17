#include "why_lib.h"
#include "declarations.h"
#include "game.h"
#include "board_inline.h"
#include "position_inline.h"
#include "why_hash_table_diagnostics.h"

#include <time.h>
#include <stdio.h>

static void _display_solution(const Game* game)
{
    Array*      path;
    int_signed  n;

    path = get_solution(game, game->current_board);
    n = 0;

    while (n < array_size(path))
    {
        print_board(array_at(path, n));
        n ++;
    }

    array_destroy(path);
}

static void _display_last(const Game* game)
{
    print_board(game->current_board);
}

static void _display_time(const Game* game, clock_t start)
{
    clock_t time;

    time = clock();
    printf("Total time elapsed: %f s.\n", time_diff(time, start));
    printf("Time spent solving the puzzle: %f s.\n", time_diff(time, game->game_created));
}

static void _display_total_size(const Game* game)
{
    printf("Total number of nodes created: %lld\n", game_get_number_of_boards(game));
}

static void _display_queue_size(const Game* game)
{
    printf("Nodes in queue: %lld\n", game_get_queue_size(game));
}

static void _display_solution_size(const Game* game)
{
    Array* path;

    path = get_solution(game, game->current_board);
    printf("Path length from initial state: %lld\n", array_size(path));

    array_destroy(path);
}

void run(Game* game, const Config* config, clock_t start)
{
    game_play(game);

    if (config_all_boards(config))
        _display_solution(game);

    if (config_last_board(config))
        _display_last(game);

    if (config_created(config))
        _display_total_size(game);

    if (config_path_length(config))
        _display_solution_size(game);

    if (config_time(config))
        _display_time(game, start);

    if (config_queue(config))
        _display_queue_size(game);
}