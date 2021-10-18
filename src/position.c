
#include "why_definitions.h"
#include "definitions.h"
#include "position.h"
#include "why_macros.h"

short row_from_index(short index, short side_size)
{
    return index / side_size;
}

short col_from_index(short index, short side_size)
{
    return index % side_size;
}

Position position_from_index(short index, short side_size)
{
    return (Position){row_from_index(index, side_size), col_from_index(index, side_size)};
}

short index_from_position(Position position, short side_size)
{
    return position.row * side_size + position.col;
}

Position position_diff(Position lhs, Position rhs)
{
    return (Position){lhs.row - rhs.row, lhs.col - rhs.col};
}

unsigned short position_vector_length(Position position)
{
    return ABS(position.row) + ABS(position.col);
}

Position get_intended_zero_position(short side_size)
{
    return (Position){side_size - 1, side_size - 1};
}

Position get_intended_position(short value, short side_size)
{
    return value ? (Position)position_from_index(value - 1, side_size) : get_intended_zero_position(side_size);
}

short index_above(short index, short side_size)
{
    return index - side_size;
}

short index_below(short index, short side_size)
{
    return index + side_size;
}

short index_leftward(short index, short side_size)
{
    return index % side_size == 0 ? -1 : index - 1;
}

short index_rightward(short index, short side_size)
{
    return index % side_size == side_size - 1 ? -1 : index + 1;
}

bool index_is_valid(short index, short total_size)
{
    return (index >= 0) && (index < total_size);
}