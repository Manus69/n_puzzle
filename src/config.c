#include "config.h"
#include "why_lib.h"
#include "declarations.h"

#include <assert.h>
#include <stdio.h>

#define SEPARATOR       '='
#define TRUE_STRING     "true"
#define FALSE_STRING    "false"
#define MHTN_STRING     "manhattan"

static const char* flag_string_values[] =
{
    "metric",
    "display_last_board",
    "display_all_boards",
    "display_time",
    "display_created",
    "display_visited",
    "display_queue",
    "display_path_length",
    0,
};

static String* _get_string_value(const String* string)
{
    String*     value;
    int_signed  n;

    if ((n = string_index_of(string, SEPARATOR)))
        return error_set(WHY_ERROR_PARSE, NULL);

    value = string_substring_end(string, n + 1);
    value = string_trimD(value);

    return value;
}

static String* _get_string_starting_with(const Array* strings, const char* start)
{
    int_signed  n;
    String*     string;

    n = 0;
    while (n < array_size(strings))
    {
        string = array_at(strings, n);

        if (string_starts_with(string, start))
            return string;
        
        n ++;
    }

    return NULL;
}

static void _set_bool_field(Config* config, enum FIELDS field, const String* string_value)
{
    bool    value;
    char*   characters;

    characters = string_get_characters(string_value);
    if (cstr_compare(characters, TRUE_STRING) == 0)
        value = true;
    else if (cstr_compare(characters, FALSE_STRING) == 0)
        value = false;
    else
        error_set(WHY_ERROR_PARSE, NULL);
    
    config->flags[field] = value;
}

static void _set_metric(Config* config, const String* string_value)
{
    char* characters;

    characters = string_get_characters(string_value);
    if (cstr_compare(characters, MHTN_STRING) == 0)
        config->metric = metric_mhtn_all;
    else
        assert(0);
}

static void _set_field(Config* config, enum FIELDS field, const String* string_value)
{
    if (field == METRIC)
        _set_metric(config, string_value);
    else
        _set_bool_field(config, field, string_value);
}

static String* _get_string_value_for_field(enum FIELDS field, const Array* strings)
{
    String* string;
    String* string_value;

    string = _get_string_starting_with(strings, flag_string_values[field]);
    if (!string)
        string_value = string_create("false");
    else
        string_value = _get_string_value(string);

    return string_value;
}

static void _config_init(Config* config, const Array* strings)
{
    enum FIELDS field;
    String*     string_value;

    field = 0;
    while (field < _SENTINEL)
    {
        string_value = _get_string_value_for_field(field, strings);
        _set_field(config, field, string_value);

        //
        printf("%d ", field);
        print_string(string_value);
        //


        field ++;
    }

    if (config->flags[D_L_BOARD] && config->flags[D_A_BOARDS])
        config->flags[D_L_BOARD] = false;
}

Config* config_create()
{
    Config* config;
    Array*  lines;

    if (!(lines = get_all_linesAFN(CONFIG_FILE_NAME)))
        return NULL;
    
    config = allocate(sizeof(Config));
    _config_init(config, lines);

    if (WHY_ERROR)
    {
        config_destroy(config);
        array_destroy(lines);

        return NULL;
    }

    return config;
}

void config_destroy(Config* config)
{
    free(config);
}