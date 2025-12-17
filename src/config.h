
#ifndef CONFIG_H
#define CONFIG_H

#include "standard_lib.h"

#define MAX_DEPTH 64

// 1. D'abord définir le type
typedef struct {
    int depth;
} Config;

// 2. Fonctions d'accès (encapsulation)
int get_depth(void);
void set_depth(int depth_value);

void init_config(int depth);
void free_config();

#endif // CONFIG_H
