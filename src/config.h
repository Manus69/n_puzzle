#ifndef CONFIG_H
#define CONFIG_H

#include "why_definitions.h"
#include "definitions.h"

#define CONFIG_FILE_NAME "../config.txt"

enum FIELDS
{
    D_L_BOARD,
    D_A_BOARDS,
    D_TIME, 
    D_CREATED,
    D_VISITED,
    D_QUEUE,
    D_PATH_LENGTH,
    METRIC,
    _SENTINEL
};

struct Config
{
    bool flags[_SENTINEL];

    int_signed (*metric)(const Board *);
};

#endif
