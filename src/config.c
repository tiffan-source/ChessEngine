
#include "config.h"

Config* global_config = NULL;

void init_config(int depth)
{
    global_config = (Config*)malloc(sizeof(Config));
    if (global_config != NULL) {
        global_config->depth = depth;
    }
}

void free_config()
{
    if (global_config != NULL) {
        free(global_config);
        global_config = NULL;
    }
}

Config* get_config()
{
    return global_config;
}
