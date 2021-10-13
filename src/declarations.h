#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "why_lib.h"
#include "definitions.h"

//support
byte            represent_number(const char* number_string);
int_unsigned    hash_board(const Board* board);

//board
Board*          board_create(byte* values);
Board*          board_create_register(byte* values);
Board*          board_create_size(byte* values, int_signed size);
Board*          board_copy(const Board* board);
bool            board_register(const Board* board);
bool            board_exists(const Board* board);
void            board_destroy(Board* board);
byte            board_at(const Board* board, byte n);
byte            board_atG(const Board* board, byte row, byte col);
int_signed      board_compare(const Board* lhs, const Board* rhs);
int_signed      board_compare_values(const Board* lhs, const Board* rhs);
int_signed      _get_board_mem_size();
byte*           _board_get_values_pointer(const Board* board);
Board*          board_up(const Board* board);
Board*          board_down(const Board* board);
Board*          board_left(const Board* board);
Board*          board_right(const Board* board);
byte            map_to_index(byte row, byte col);
byte            map_to_row(byte index);
byte            map_to_col(byte index);
byte            board_index_of_zero(const Board* board);
byte            board_row_of_zero(const Board* board);
byte            board_col_of_zero(const Board* board);
void            board_set_previous(Board* board, const Board* previous);

//state
State*          state_create(byte* values);
void            state_destroy(State* state);
bool            state_process_current_board(State* state);
Board*          state_solve(State* state);

//game
Game*           game_create(int_signed total_size);
void            game_destroy(Game* game);
int_unsigned    game_get_hash_table_capacity(const Game* game);

//metric
int_signed      metric_manhattan(const Board* board);
int_signed      metric_manhattanN(const Board* board);

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