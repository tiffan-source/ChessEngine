
#ifdef TEST

#include "unity.h"

#include "pawns_moves.h"
#include "board.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_generate_pawns_quiet_moves_from_square_a2_for_white(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(WHITE, A2);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, A3);
    expected = set_bit_on_bitboard(expected, A4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_quiet_moves_from_square_b3_for_white(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(WHITE, B3);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, B4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_quiet_moves_from_square_g7_for_white(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(WHITE, G7);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, G8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_quiet_moves_from_square_h8_for_white(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(WHITE, H8);
    Bitboard expected = 0x0ULL;

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}


void test_generate_pawns_quiet_moves_from_square_a7_for_black(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(BLACK, A7);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, A6);
    expected = set_bit_on_bitboard(expected, A5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_quiet_moves_from_square_d5_for_black(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(BLACK, D5);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, D4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_quiet_moves_from_square_d1_for_black(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(BLACK, D1);
    Bitboard expected = 0x0ULL;

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_quiet_moves_from_square_c2_for_black(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(BLACK, C2);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, C1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}



void test_generate_pawns_capture_moves_from_square_e3_for_white(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(WHITE, E3);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, D4);
    expected = set_bit_on_bitboard(expected, F4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_a7_for_white(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(WHITE, A7);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, B8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_h4_for_white(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(WHITE, H4);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, G5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_c5_for_white(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(WHITE, C5);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, B6);
    expected = set_bit_on_bitboard(expected, D6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}




void test_generate_pawns_capture_moves_from_square_h7_for_black(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(BLACK, H7);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, G6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_b2_for_black(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(BLACK, B2);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, A1);
    expected = set_bit_on_bitboard(expected, C1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_f6_for_black(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(BLACK, F6);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, E5);
    expected = set_bit_on_bitboard(expected, G5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_a5_for_black(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(BLACK, A5);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, B4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}
#endif // TEST