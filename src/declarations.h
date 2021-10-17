#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "why_definitions.h"
#include "definitions.h"

//support
Board*          get_solved_board(int_signed total_size);
int_signed      count_transpositions(const Board* board);
byte            check_parity(const Board* board);

//solution
Array*          get_solution(const Board* final_board);

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
int_signed      metric_mhtn_all(const Board* board);
int_signed      metric_mhtn_zero(const Board* board);
int_signed      metric_mhtn_after_swap(const Board* board, byte j, byte k);

//io
byte*           input_get_bytes(const Array* strings);
byte*           input_get_bytesCSTR(const char* string);
void            print_current_board(const Game* state);
void            print_board(const Board* board);
Game*           get_game_from_file(const char* file_name, int_signed (*metric)(const Board *));

//hash
int_unsigned    hash_board(const Board* board);
int_unsigned    hash_board_size(const Board* board, int_signed size);

//debug
byte*           debug_get_bytes(const char* string);


#endif