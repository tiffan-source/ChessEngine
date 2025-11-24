
#ifdef TEST

#include "unity.h"

#include "knights_moves.h"
#include "board.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_generate_knights_moves_from_c6_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_knights_moves_from_square(C6);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, B8);
    expected = set_bit_on_bitboard(expected, D8);
    expected = set_bit_on_bitboard(expected, A7);
    expected = set_bit_on_bitboard(expected, E7);
    expected = set_bit_on_bitboard(expected, A5);
    expected = set_bit_on_bitboard(expected, E5);
    expected = set_bit_on_bitboard(expected, B4);
    expected = set_bit_on_bitboard(expected, D4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_knights_moves_from_a4_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_knights_moves_from_square(A4);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, B6);
    expected = set_bit_on_bitboard(expected, C5);
    expected = set_bit_on_bitboard(expected, C3);
    expected = set_bit_on_bitboard(expected, B2);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_knights_moves_from_b3_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_knights_moves_from_square(B3);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, A5);
    expected = set_bit_on_bitboard(expected, C5);
    expected = set_bit_on_bitboard(expected, D4);
    expected = set_bit_on_bitboard(expected, D2);
    expected = set_bit_on_bitboard(expected, C1);
    expected = set_bit_on_bitboard(expected, A1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_knights_moves_from_e8_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_knights_moves_from_square(E8);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, D6);
    expected = set_bit_on_bitboard(expected, F6);
    expected = set_bit_on_bitboard(expected, C7);
    expected = set_bit_on_bitboard(expected, G7);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

#endif // TEST
