#include "declarations.h"
#include "definitions.h"
#include "why_lib.h"
#include "why_definitions.h"

#include <assert.h>

#define COMMENT_SYMBOL "#"

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

static void _process_first_string(String* string)
{
    int_signed value;

    value = convert_to_int(string_get_characters(string));

    string_destroy(string);
}

Array* process_string_array(const Array* string_array)
{
    Array*      number_strings;
    String*     string;
    int_signed  n;

    if (!string_array)
        return NULL;
    
    number_strings = array_create_with_capacity(copy_shallow, string_destroy, array_size(string_array));
    n = 0;
    while (n < array_size(string_array))
    {
        string = array_at(string_array, n);
        if (!string_starts_with(string, COMMENT_SYMBOL))
        {
            string = string_trim(string);
            array_push(number_strings, string);
        }

        n ++;
    }

    string = array_pop_front(number_strings);
    _process_first_string(string);

    return number_strings;
}

Array* input_get_strings_from_stdin()
{
    Array* lines;
    Array* number_strings;

    if (!(lines = get_all_linesA(STDIN_FILENO)))
        return NULL;

    number_strings = process_string_array(lines);

    array_destroy(lines);

    return number_strings;
}

Array* input_get_strings_from_file(const char* file_name)
{
    Array* lines;
    Array* number_strings;

    if (!(lines = get_all_linesAFN(file_name)))
        return NULL;
    
    number_strings = process_string_array(lines);

    array_destroy(lines);

    return number_strings;
}

static Game* _get_game(Array* number_strings, int_signed (*metric)())
{
    Game*   game;
    byte*   bytes;

    bytes = input_get_bytes(number_strings);
    game = game_create(bytes, array_size(number_strings), metric);

    array_destroy(number_strings);
    free(bytes);

    return game;
}

Game* get_game_from_file(const char* file_name, int_signed (*metric)(const Board *))
{
    Array*  number_strings;

    if (!(number_strings = input_get_strings_from_file(file_name)))
        return NULL;
    
    return _get_game(number_strings, metric);
}

Game* get_game_from_stdin(int_signed (*metric)(const Board *))
{
    Array* number_strings;

    if (!(number_strings = input_get_strings_from_stdin()))
        return NULL;
    
    return _get_game(number_strings, metric);
}