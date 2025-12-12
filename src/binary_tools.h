
#ifndef BINARY_TOOLS_H
#define BINARY_TOOLS_H

#include "standard_lib.h"


#define GET_LSB_INDEX(value) ((value) ? __builtin_ctzll(value) : -1)

#define COUNT_BITS_SET(v) ((int)__builtin_popcountll((unsigned long long)(v)))

#define RANDOM_U64_FEWBITS() (random_U64() & random_U64() & random_U64())

#define HASH_FUNCTION_FOR_INDEXING_U64_CONFIGURATION(blocker_configuration, magic_number, relevant_bits) \
    ((((blocker_configuration) * (magic_number)) >> (64 - relevant_bits)))


typedef unsigned long long int U64;

extern const U64 pre_calculated_bit_shifts[64];

char* string_representation_of_U64(U64 value);
U64 random_U64();

#endif // BINARY_TOOLS_H
