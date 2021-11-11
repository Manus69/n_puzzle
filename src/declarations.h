#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "why_definitions.h"
#include "definitions.h"

#include <time.h>

void            run(Game* game, const Config* config, clock_t start);

//support
Board*          get_solved_board(int_signed total_size);
int_signed      count_transpositions(const Board* board);
int_signed      count_misplaced_elements(const Board* board);
byte            check_parity(const Board* board);
double          time_diff(clock_t start, clock_t end);
void*           no_op(void* pointer);

//solution
Array*          get_solution(const Game* game, const Board* final_board);

//board
void            board_init(Board* board, byte* values, byte n_cells);
void            board_init_fields(Board* board, const Board* previous, byte ep_index);
Board*          board_create(byte* values, byte n_cells);
Board*          board_copy(const Board* board);
void            board_destroy(Board* board);
int_signed      board_compare_values(const Board* lhs, const Board* rhs);
int_signed      board_compare_hash(const Board* lhs, const Board* rhs);
int_signed      board_compare_metric_vals(const Board* lhs, const Board* rhs);
bool            _board_up(Board* board);
bool            _board_down(Board* board);
bool            _board_left(Board* board);
bool            _board_right(Board* board);
Board*          board_up(const Game* game, const Board* board);
Board*          board_down(const Game* game, const Board* board);
Board*          board_left(const Game* game, const Board* board);
Board*          board_right(const Game* game, const Board* board);
Board*          board_create_register(byte* values, byte n_cells);
bool            board_register(Game* game, const Board* board);
bool            board_exists(Game* game, const Board* board);
void            board_compute_distance(Board* board, int_signed (*metric)(const Board*));
int_signed      board_compare_metric_vals(const Board* lhs, const Board* rhs);

//game
Game*           game_create(byte* values, int_signed total_size, int_signed (*metric)(const Board *));
void            game_destroy(Game* game);
int_signed      game_get_number_of_boards(const Game* game);
int_unsigned    game_get_hash_table_capacity(const Game* game);
int_signed      game_get_visited_board_count(const Game* game);
int_signed      game_get_queue_size(const Game* game);
Board*          game_play(Game* game);

//metric
int_signed      metric_mhtn_at_index(const Board* board, byte index);
int_signed      metric_mhtn(const Board* board);
int_signed      metric_mhtn_zero(const Board* board);
int_signed      metric_mhtn_after_swap(const Board* board, byte j, byte k);
int_signed      metric_misplaced(const Board* board);
int_signed      metric_misplaced_after_swap(const Board* board, byte j, byte k);
int_signed      metric_uniform(const Board* board);
int_signed      metric_uniform_after_swap(const Board* board, byte j, byte k);

//io
byte*           input_get_bytes(const Array* strings);
byte*           input_get_bytesCSTR(const char* string);
void            print_current_board(const Game* state);
void            print_board(const Board* board);
Game*           get_game_from_file(const char* file_name, const Config* config);
Game*           get_game_from_stdin(const Config* config);
void            display_usage();
void            print_arrow_down();
void            print_arrow_downT();
void            print_arraw_up();
void            _display_initial_state(const Game* game);
void            _display_run_time(clock_t start, clock_t end);
void            _display_failure(const Game* game);

//hash
int_unsigned    hash_board(const Board* board);
int_unsigned    hash_board_size(const Board* board, int_signed size);

//config
Config*         config_create();
void            config_destroy(Config* config);
void*           config_get_metric(const Config* config);
bool            config_last_board(const Config* config);
bool            config_all_boards(const Config* config);
bool            config_path_length(const Config* config);
bool            config_time(const Config* config);
bool            config_created(const Config* config);
bool            config_visied(const Config* config);
bool            config_queue(const Config* config);
bool            config_initial(const Config* config);

//debug
byte*           debug_get_bytes(const char* string);

//
//board
byte*           board_get_values(const Board* board);
byte            board_get_side_size(const Board* board);
byte            board_get_total_size(const Board* board);
int_signed      _get_board_mem_size(byte n_cells);
byte            board_at(const Board* board, byte n);
byte            board_set(Board* board, byte value, byte index);
byte            board_at_position(const Board* board, Position position);
byte            board_get_index_of_zero(const Board* board);
Position        board_get_position_of_zero(const Board* board);
void            board_set_previous(Board* board, const Board* previous);
void            board_swap(Board* board, byte l_index, byte r_index);
void            board_compute_metric(Board* board, int_signed (*metric)(const Board*));

//position
short           row_from_index(short index, short side_size);
short           col_from_index(short index, short side_size);
Position        position_from_index(short index, short side_size);
short           index_from_position(Position position, short side_size);
Position        position_diff(Position lhs, Position rhs);
unsigned short  position_vector_length(Position position);
Position        get_intended_zero_position(short side_size);
short           get_intended_index(short value, short side_size);
Position        get_intended_position(short value, short side_size);
short           index_above(short index, short side_size);
short           index_below(short index, short side_size);
short           index_leftward(short index, short side_size);
short           index_rightward(short index, short side_size);
bool            index_is_valid(short index, short total_size);
bool            position_equal(Position lhs, Position rhs);
bool            value_in_correct_position(short value, short index, short side_size);

#endif