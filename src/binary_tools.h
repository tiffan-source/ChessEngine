
#ifndef BINARY_TOOLS_H
#define BINARY_TOOLS_H

#include "standard_lib.h"

typedef unsigned long long int U64;

char* string_representation_of_U64(U64 value);
int get_lsb_index(U64 value);
int count_bits_set(U64 value);
int hash_function_for_indexing_U64_configuration(U64 blocker_configuration, U64 magic_number, int relevant_bits);
U64 random_U64_fewbits();

#endif // BINARY_TOOLS_H
