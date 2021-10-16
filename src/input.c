#include "declarations.h"
#include "definitions.h"
#include "why_lib.h"

#include <assert.h>

static byte* _to_bytes(const Array* strings, int_signed size)
{
    String*     string;
    int_signed  number;
    int_signed  n;
    byte        guard[size];
    byte*       bytes;

    memory_set(guard, 0, size);
    bytes = allocate(sizeof(byte) * size);
    n = 0;
    while (n < size)
    {
        string = array_at(strings, n);
        number = convert_to_intS(string);

        if (number >= size || number < 0 || guard[number])
            assert(0); //dont forget to free bytes
        
        bytes[n] = number;
        guard[number] = 1;

        n ++;
    }

    return bytes;
}

//must contain value strings only
byte* input_get_bytes(const Array* strings)
{
    int_signed size;

    if (!strings)
        return NULL;
    
    size = array_size(strings);
    if (!math_is_perfect_square(size) || size < MIN_TOTAL_SIZE)
        assert(0);

    return _to_bytes(strings, size);
}

byte* input_get_bytesCSTR(const char* string)
{
    Array* number_strings;

    number_strings = string_splitCSTR(string, ' ');

    return input_get_bytes(number_strings);
}


//static Array* _filter_strings(const Array* input_strings); or something?