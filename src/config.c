#include "config.h"
#include "why_lib.h"
#include "declarations.h"

#include <assert.h>
#include <stdio.h>

#define SEPARATOR           '='
#define TRUE_STRING         "true"
#define FALSE_STRING        "false"
#define MHTN_STRING         "manhattan"
#define MISPLACED_STRING    "misplaced"
#define UNIFORM_STRING      "uniform"

static const char* flag_string_values[] =
{
    "display_last_board",
    "display_path",
    "display_time",
    "display_created",
    "display_visited",
    "display_queue",
    "display_path_length",
    "display_initial_board_stats",
    "metric",
    0,
};

static String* _get_string_value(const String* string)
{
    String*     value;
    int_signed  n;

    n = string_index_of(string, SEPARATOR);

    if (n == NOT_FOUND)
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

    value = false;
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
        config->metric = metric_mhtn;
    else if (cstr_compare(characters, MISPLACED_STRING) == 0)
        config->metric = metric_misplaced;
    else if (cstr_compare(characters, UNIFORM_STRING) == 0)
        config->metric = metric_uniform;
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
    char*   field_string;

    field_string = (char *)flag_string_values[field];
    string = _get_string_starting_with(strings, field_string);
    if (!string)
        string_value = string_create("false");
    else
        string_value = _get_string_value(string);

    // string_destroy(string);

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
        string_destroy(string_value);

        field ++;
    }

    if (config->flags[D_L_BOARD] && config->flags[D_PATH])
        config->flags[D_L_BOARD] = false;
}

Config* config_create()
{
    Config* config;
    Array*  lines;

    if (!(lines = get_all_linesAFN(CONFIG_FILE_NAME)))
        return error_set(WHY_ERROR_FILE, NULL);
    
    config = allocate(sizeof(Config));
    _config_init(config, lines);
    array_destroy(lines);

    if (WHY_ERROR)
    {
        config_destroy(config);
        // error_display();

        return NULL;
    }

    return config;
}

void config_destroy(Config* config)
{
    free(config);
}