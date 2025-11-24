
#include "binary_tools.h"

char* string_representation_of_U64(U64 value)
{
    char* result = (char*)malloc(sizeof(char) * (8 * 8 * 2 + 1));
    int bit, index;

    if (!result)
        return NULL;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            index = (i * 8 + j);
            bit = (value & (1ULL << index)) ? 1 : 0;

            sprintf(result + (i * 16 + j * 2), "%d%c", bit, (j == 7) ? '\n' : ' ');
        }
    }

    return result;
}

int get_lsb_index(U64 value)
{
    if (value == 0)
        return -1;

    return __builtin_ctzll(value);
}

int count_bits_set(U64 value)
{
    return __builtin_popcountll(value);
}

U64 random_U64() {
  U64 u1, u2, u3, u4;
  u1 = (U64)(random()) & 0xFFFF; u2 = (U64)(random()) & 0xFFFF;
  u3 = (U64)(random()) & 0xFFFF; u4 = (U64)(random()) & 0xFFFF;
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

U64 random_U64_fewbits() {
  return random_U64() & random_U64() & random_U64();
}

int hash_function_for_indexing_U64_configuration(U64 blocker_configuration, U64 magic_number, int relevant_bits)
{
    return (int)((blocker_configuration * magic_number) >> (64 - relevant_bits));
}
