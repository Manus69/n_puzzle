#include "why_lib.h"
#include "game.h"
#include "definitions.h"

#include <assert.h>

byte represent_number(const char* number_string)
{
    int_signed number;

    number = convert_to_int(number_string);
    if (number < 0 || number > MAX_CELL_VALUE)
        assert(0);
    
    return number;
}
