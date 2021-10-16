#ifndef POSITION_INLINE_H
#define POSITION_INLINE_H

#include "why_definitions.h"
#include "definitions.h"
#include "position.h"

inline short row_from_index(short index, short side_size)
{
    return index / side_size;
}

inline short col_from_index(short index, short side_size)
{
    return index % side_size;
}

inline Position position_from_index(short index, short side_size)
{
    return (Position){row_from_index(index, side_size), col_from_index(index, side_size)};
}

inline short index_from_position(Position position, short side_size)
{
    return position.row * side_size + position.col;
}

inline Position position_diff(Position lhs, Position rhs)
{
    return (Position){lhs.row - rhs.row, lhs.col - rhs.col};
}

inline unsigned short position_vector_length(Position position)
{
    return ABS(position.row) + ABS(position.col);
}

inline Position get_intended_zero_position(short side_size)
{
    return (Position){side_size - 1, side_size - 1};
}

inline Position get_intended_position(short value, short side_size)
{
    return value ? (Position)position_from_index(value - 1, side_size) : get_intended_zero_position(side_size);
}

inline short index_above(short index, short side_size)
{
    return index - side_size;
}

inline short index_below(short index, short side_size)
{
    return index + side_size;
}

inline short index_leftward(short index, short side_size)
{
    return index % side_size == 0 ? -1 : index - 1;
}

inline short index_rightward(short index, short side_size)
{
    return index % side_size == side_size - 1 ? -1 : index + 1;
}

inline bool index_is_valid(short index, short total_size)
{
    return (index >= 0) && (index < total_size);
}

#endif