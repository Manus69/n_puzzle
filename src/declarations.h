#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "why_lib.h"
#include "definitions.h"

//support
byte            represent_number(const char* number_string);
int_unsigned    hash_board(const Board* board);

//board
Board*          board_create(byte* values);
void            board_destroy(Board* board);
byte            board_at(const Board* board, byte n);
byte            board_atG(const Board* board, byte row, byte col);
int_signed      board_compare(const Board* lhs, const Board* rhs);
int_signed      _get_board_mem_size();
Board*          board_up(const Board* board);
Board*          board_down(const Board* board);
Board*          board_left(const Board* board);
Board*          board_right(const Board* board);

//state
State*          state_create(byte* values);
void            state_destroy(State* state);

//game
Game*           game_create(int_signed total_size);
void            game_destroy(Game* game);
int_unsigned    game_get_hash_table_capacity(const Game* game);

//io
byte*           input_get_bytes(const Array* strings);
void            print_current_board(const State* state);

//hash
int_unsigned    hash_board(const Board* board);

//debug
byte*           debug_get_bytes(const char* string);

#endif