#ifndef POSITION_H
#define POSITION_H

#include "why_definitions.h"
#include "definitions.h"
#include "why_macros.h"

struct Position
{
    short row;
    short col;
};

inline byte row_from_index(byte index, byte side_size)
{
    return index / side_size;
}

inline byte col_from_index(byte index, byte side_size)
{
    return index % side_size;
}

inline Position position_from_index(byte index, byte side_size)
{
    return (Position){row_from_index(index, side_size), col_from_index(index, side_size)};
}

inline byte index_from_position(Position position, byte side_size)
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

inline Position get_intended_zero_position(byte side_size)
{
    return (Position){side_size - 1, side_size - 1};
}

inline Position get_intended_position(byte value, byte side_size)
{
    return value ? (Position)position_from_index(value - 1, side_size) : get_intended_zero_position(side_size);
}

inline short index_above(byte index, byte side_size)
{
    return (short)index - side_size;
}

inline short index_below(byte index, byte side_size)
{
    return (short)index + side_size;
}

inline short index_leftward(byte index, byte side_size)
{
    return index % side_size == 0 ? -1 : index - 1;
}

inline short index_rightward(byte index, byte side_size)
{
    return index % side_size == side_size - 1 ? -1 : index + 1;
}

inline bool index_is_valid(short index, byte total_size)
{
    return (index >= 0) && (index < total_size);
}

#endif