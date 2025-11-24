
#include "board.h"

char* string_bitboard_on_chess_board(Bitboard position)
{
    char *result = (char*)malloc(sizeof(char) * (9 * 9 * 2 + 1 ));
    int bit, index;

    if (!result)
        return NULL;

    for (int i = 0; i <= 7; i++)
    {
        sprintf(result + (i * 18), "%c ", '8' - i);

        for (int j = 1; j <= 8; j++)
        {
            index = (i * 8 + (j - 1));
            bit = (position & (1ULL << index)) ? 1 : 0;

            sprintf(result + (i * 18 + j * 2), "%d%c", bit, (j == 8) ? '\n' : ' ');
        }
    }
    sprintf(result + (8 * 18), "  a b c d e f g h\n");

    return result;
}

Bitboard set_bit_on_bitboard(Bitboard bitboard, Square square)
{
    return bitboard | (1ULL << square);
}

Bitboard clear_bit_on_bitboard(Bitboard bitboard, Square square)
{
    return bitboard & ~(1ULL << square);
}

int bit_on_bitboard_hit_8_rank(Bitboard bitboard)
{
    int hit = bitboard & RANK_8 ? 1 : 0;
    return hit;
}

int bit_on_bitboard_hit_7_rank(Bitboard bitboard)
{
    int hit = bitboard & RANK_7 ? 1 : 0;
    return hit;
}

int bit_on_bitboard_hit_1_rank(Bitboard bitboard)
{
    int hit = bitboard & RANK_1 ? 1 : 0;
    return hit;
}

int bit_on_bitboard_hit_2_rank(Bitboard bitboard)
{
    int hit = bitboard & RANK_2 ? 1 : 0;
    return hit;
}

int bit_on_bitboard_hit_a_file(Bitboard bitboard)
{
    int hit = bitboard & FILE_A ? 1 : 0;
    return hit;
}

int bit_on_bitboard_hit_b_file(Bitboard bitboard)
{
    int hit = bitboard & FILE_B ? 1 : 0;
    return hit;
}

int bit_on_bitboard_hit_h_file(Bitboard bitboard)
{
    int hit = bitboard & FILE_H ? 1 : 0;
    return hit;
}

int bit_on_bitboard_hit_g_file(Bitboard bitboard)
{
    int hit = bitboard & FILE_G ? 1 : 0;
    return hit;
}