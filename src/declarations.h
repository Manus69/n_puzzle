#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "why_definitions.h"
#include "definitions.h"

//support
int_unsigned    hash_board(const Board* board);

//board
void            board_init(Board* board, byte* values, byte n_cells);
void            board_init_fields(Board* board, const Board* previous, byte ep_index);
Board*          board_create(byte* values, byte n_cells);
Board*          board_copy(const Board* board);
void            board_destroy(Board* board);
int_signed      board_compare_values(const Board* lhs, const Board* rhs);
int_signed      board_compare_hash(const Board* lhs, const Board* rhs);
bool            _board_up(Board* board);
bool            _board_down(Board* board);
bool            _board_left(Board* board);
bool            _board_right(Board* board);
Board*          board_up(const Board* board);
Board*          board_down(const Board* board);
Board*          board_left(const Board* board);
Board*          board_right(const Board* board);
Board*          board_create_register(byte* values, byte n_cells);
bool            board_register(const Board* board);
bool            board_exists(const Board* board);

//state
State*          state_create(byte* values, const Game* game);
void            state_destroy(State* state);
bool            state_process_current_board(State* state);
Board*          state_solve(State* state);

//game
Game*           game_create(int_signed total_size);
void            game_destroy(Game* game);
int_unsigned    game_get_hash_table_capacity(const Game* game);

//metric
int_signed      get_manhattan_distnace(const Board* board, byte index);
int_signed      get_all_points_distance(const Board* board);
int_signed      get_manhattan_distance_of_zero(const Board* board);
int_signed      get_manhattan_distance_of_zeroN(const Board* board);
int_signed      board_compare_manhattan_zero(const Board* lhs, const Board* rhs);

//io
byte*           input_get_bytes(const Array* strings);
void            print_current_board(const State* state);
void            print_board(const Board* board);

//hash
int_unsigned    hash_board(const Board* board);
int_unsigned    hash_board_size(const Board* board, int_signed size);

//debug
byte*           debug_get_bytes(const char* string);

#endif