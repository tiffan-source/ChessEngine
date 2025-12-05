
#ifndef CONFIG_H
#define CONFIG_H

#include "standard_lib.h"

#define GET_DEPTH_FROM_CONFIG(config) ((config)->depth)
#define SET_DEPTH_IN_CONFIG(config, depth_value) ((config)->depth = (depth_value))

typedef struct {
    int depth;
} Config;

void init_config(int depth);
void free_config();
Config* get_config();

#endif // CONFIG_H
