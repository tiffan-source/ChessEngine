
#ifdef TEST

#include "unity.h"

#include "king_moves.h"
#include "board.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_generate_king_moves_from_a8_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_king_moves_from_square(A8);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, A7);
    expected = set_bit_on_bitboard(expected, B7);
    expected = set_bit_on_bitboard(expected, B8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_king_moves_from_d5_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_king_moves_from_square(D5);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, C4);
    expected = set_bit_on_bitboard(expected, D4);
    expected = set_bit_on_bitboard(expected, E4);
    expected = set_bit_on_bitboard(expected, C5);
    expected = set_bit_on_bitboard(expected, E5);
    expected = set_bit_on_bitboard(expected, C6);
    expected = set_bit_on_bitboard(expected, D6);
    expected = set_bit_on_bitboard(expected, E6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

#endif // TEST
