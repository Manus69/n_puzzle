#ifndef INLINE_DECLARATIONS_H
#define INLINE_DECLARATIONS_H

#include "definitions.h"
#include "why_definitions.h"

extern inline byte*             board_get_values(const Board* board);
extern inline byte              board_get_total_size(const Board* board);
extern inline int_signed        _get_board_mem_size(byte n_cells);
extern inline byte              board_at(const Board* board, byte n);
extern inline byte              board_at_position(const Board* board, Position position);
extern inline byte              board_get_index_of_zero(const Board* board);
extern inline Position          board_get_position_of_zero(const Board* board);
extern inline void              board_set_previous(Board* board, const Board* previous);
extern inline byte              row_from_index(byte index, byte side_size);
extern inline byte              col_from_index(byte index, byte side_size);
extern inline Position          position_from_index(byte index, byte side_size);
extern inline byte              index_from_position(Position position, byte side_size);
extern inline Position          position_diff(Position lhs, Position rhs);
extern inline unsigned short    position_vector_length(Position position);
extern inline Position          get_intended_zero_position(byte side_size);
extern inline Position          get_intended_position(byte value, byte side_size);
extern inline short             index_above(byte index, byte side_size);
extern inline short             index_below(byte index, byte side_size);
extern inline short             index_leftward(byte index, byte side_size);
extern inline short             index_rightward(byte index, byte side_size);
extern inline bool              index_is_valid(short index, byte total_size);

#endif