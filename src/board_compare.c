#include "board.h"
#include "definitions.h"
#include "declarations.h"
#include "why_definitions.h"
#include "position.h"
#include "inline_declarations.h"

int_signed board_compare_values(const Board* lhs, const Board* rhs)
{
    int_signed n;
    int_signed total_size;

    n = 0;
    total_size = board_get_total_size(lhs);
    while (n < total_size)
    {
        if (lhs->values[n] != rhs->values[n])
            break ;
        n ++;
    }

    return n == total_size ? 0 : rhs->values[n] - lhs->values[n];
}

int_signed board_compare_hash(const Board* lhs, const Board* rhs)
{
    if (!lhs && !rhs)
        return 0;

    if (!lhs)
        return 1;

    if (!rhs)
        return -1;

    if (lhs->hash_value == rhs->hash_value)
        return board_compare_values(lhs, rhs);

    return rhs->hash_value - lhs->hash_value;
}

int_signed board_compare_manhattan_zero(const Board* lhs, const Board* rhs)
{
    int_signed lhs_value;
    int_signed rhs_value;

    lhs_value = get_manhattan_distance_of_zeroN(lhs);
    rhs_value = get_manhattan_distance_of_zeroN(rhs);

    return rhs_value - lhs_value;
}
