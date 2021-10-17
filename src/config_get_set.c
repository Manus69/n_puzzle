#include "config.h"

void* config_get_metric(const Config* config)
{
    return config->metric;
}

bool config_last_board(const Config* config)
{
    return config->flags[D_L_BOARD];
}

bool config_all_boards(const Config* config)
{
    return config->flags[D_A_BOARDS];
}

bool config_path_length(const Config* config)
{
    return config->flags[D_PATH_LENGTH];
}

bool config_time(const Config* config)
{
    return config->flags[D_TIME];
}

bool config_created(const Config* config)
{
    return config->flags[D_CREATED];
}

bool config_visied(const Config* config)
{
    return config->flags[D_VISITED];
}

bool config_queue(const Config* config)
{
    return config->flags[D_QUEUE];
}