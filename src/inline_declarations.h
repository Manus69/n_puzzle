// #ifndef INLINE_DECLARATIONS_H
// #define INLINE_DECLARATIONS_H

// #include "definitions.h"
// #include "why_definitions.h"

// //board
// extern inline byte*             board_get_values(const Board* board);
// extern inline byte              board_get_side_size(const Board* board);
// extern inline byte              board_get_total_size(const Board* board);
// extern inline int_signed        _get_board_mem_size(byte n_cells);
// extern inline byte              board_at(const Board* board, byte n);
// extern inline byte              board_set(Board* board, byte value, byte index);
// extern inline byte              board_at_position(const Board* board, Position position);
// extern inline byte              board_get_index_of_zero(const Board* board);
// extern inline Position          board_get_position_of_zero(const Board* board);
// extern inline void              board_set_previous(Board* board, const Board* previous);
// extern inline void              board_swap(Board* board, byte l_index, byte r_index);
// extern inline void              board_compute_metric(Board* board, int_signed (*metric)(const Board*));

// //position
// extern inline short             row_from_index(short index, short side_size);
// extern inline short             col_from_index(short index, short side_size);
// extern inline Position          position_from_index(short index, short side_size);
// extern inline short             index_from_position(Position position, short side_size);
// extern inline Position          position_diff(Position lhs, Position rhs);
// extern inline unsigned short    position_vector_length(Position position);
// extern inline Position          get_intended_zero_position(short side_size);
// extern inline Position          get_intended_position(short value, short side_size);
// extern inline short             index_above(short index, short side_size);
// extern inline short             index_below(short index, short side_size);
// extern inline short             index_leftward(short index, short side_size);
// extern inline short             index_rightward(short index, short side_size);
// extern inline bool              index_is_valid(short index, short total_size);

// #endif