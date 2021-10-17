#include "board.h"
#include "definitions.h"
#include "declarations.h"
#include "why_definitions.h"
#include "position.h"
#include "board_inline.h"

int_signed board_compare_values(const Board* lhs, const Board* rhs)
{
    int_signed n;
    int_signed total_size;

    n = 0;
    total_size = board_get_total_size(lhs);
    while (n < total_size - 1)
    {
        if (board_at(lhs, n) != board_at(rhs, n))
            break ;
        n ++;
    }

    return (int_signed)board_at(rhs, n) - (int_signed)board_at(lhs, n);
}

int_signed board_compare_hash(const Board* lhs, const Board* rhs)
{
    if (!lhs && !rhs)
        return 0;

    if (!lhs)
        return 1;

    if (!rhs)
        return -1;

    return rhs->hash_value != lhs->hash_value;
}

int_signed board_compare_metric_vals(const Board* lhs, const Board* rhs)
{
    return rhs->metric_value - lhs->metric_value;
}
