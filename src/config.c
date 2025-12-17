
#include "config.h"

static Config* global_config = NULL;

void init_config(int depth)
{
    global_config = (Config*)malloc(sizeof(Config));
    if (global_config != NULL) {
        global_config->depth = depth;
    }
}

int get_depth(void)
{
    return global_config->depth;
}

void set_depth(int depth_value)
{
    global_config->depth = depth_value;
}

void free_config()
{
    if (global_config != NULL) {
        free(global_config);
        global_config = NULL;
    }
}
