
#ifdef TEST

#include "unity.h"

#include "board.h"

void setUp(void)
{
}

void tearDown(void)
{
}

// Test board stringifying bitboards

void test_board_should_return_bitboard_on_chess_board_with_correct_length(void)
{
    Bitboard position = 0ULL;
    char* board = string_bitboard_on_chess_board(position);

    TEST_ASSERT_EQUAL_INT(9 * 9 * 2 , strlen(board));
    free(board);
}

void test_board_should_return_bitboard_0_on_chess_board(void)
{
    Bitboard position = 0ULL;
    char* board = string_bitboard_on_chess_board(position);

    const char* expect = "8 0 0 0 0 0 0 0 0\n"
                         "7 0 0 0 0 0 0 0 0\n"
                         "6 0 0 0 0 0 0 0 0\n"
                         "5 0 0 0 0 0 0 0 0\n"
                         "4 0 0 0 0 0 0 0 0\n"
                         "3 0 0 0 0 0 0 0 0\n"
                         "2 0 0 0 0 0 0 0 0\n"
                         "1 0 0 0 0 0 0 0 0\n"
                         "  a b c d e f g h\n";

    TEST_ASSERT_EQUAL_STRING(expect, board);
    free(board);
}

void test_board_should_return_bitboard_0x754AFF64A76C7B8D_on_chess_board(void)
{
    Bitboard position = 0x754AFF64A76C7B8DULL;
    char* board = string_bitboard_on_chess_board(position);

    const char* expect = "8 1 0 1 1 0 0 0 1\n"
                         "7 1 1 0 1 1 1 1 0\n"
                         "6 0 0 1 1 0 1 1 0\n"
                         "5 1 1 1 0 0 1 0 1\n"
                         "4 0 0 1 0 0 1 1 0\n"
                         "3 1 1 1 1 1 1 1 1\n"
                         "2 0 1 0 1 0 0 1 0\n"
                         "1 1 0 1 0 1 1 1 0\n"
                         "  a b c d e f g h\n";

    TEST_ASSERT_EQUAL_STRING(expect, board);
    free(board);
}

// Test board set bit on bitboard

void test_board_should_SET_BIT_ON_BITBOARD_at_square_e4(void)
{
    Bitboard bitboard = 0x0ULL;
    Bitboard updated_bitboard = SET_BIT_ON_BITBOARD(bitboard, E4);

    TEST_ASSERT_EQUAL_UINT64(0x1000000000ULL, updated_bitboard);
}

void test_board_should_SET_BIT_ON_BITBOARD_at_square_a8(void)
{
    Bitboard bitboard = 0x0ULL;
    Bitboard updated_bitboard = SET_BIT_ON_BITBOARD(bitboard, A8);

    TEST_ASSERT_EQUAL_UINT64(0x1ULL, updated_bitboard);
}


void test_board_should_SET_BIT_ON_BITBOARD_at_square_b8(void)
{
    Bitboard bitboard = 0x1ULL;
    Bitboard updated_bitboard = SET_BIT_ON_BITBOARD(bitboard, B8);

    TEST_ASSERT_EQUAL_UINT64(0x3ULL, updated_bitboard);
}

void test_board_should_clear_bit_on_bitboard_at_square_a1(void)
{
    Bitboard bitboard = 0x1000000000ULL;
    Bitboard updated_bitboard = clear_bit_on_bitboard(bitboard, A1);

    TEST_ASSERT_EQUAL_UINT64(0x1000000000ULL, updated_bitboard);
}

void test_board_should_clear_bit_on_bitboard_at_square_a8(void)
{
    Bitboard bitboard = 8548485495ULL;
    Bitboard updated_bitboard = clear_bit_on_bitboard(bitboard, A8);

    TEST_ASSERT_EQUAL_UINT64(8548485494ULL, updated_bitboard);
}

void test_board_should_clear_bit_on_bitboard_at_square_e4(void)
{
    Bitboard bitboard = 0x1000000000ULL;
    Bitboard updated_bitboard = clear_bit_on_bitboard(bitboard, E4);

    TEST_ASSERT_EQUAL_UINT64(0x0ULL, updated_bitboard);
}

// Test board bit on bitboard hit rank/file

void test_board_bit_on_bitboard_hit_8_rank_should_return_0_for_empty_bitboard(void)
{
    Bitboard bitboard = 0x0ULL;
    int hits = bit_on_bitboard_hit_8_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_8_rank_should_return_1_for_bitboard_with_d8_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, D8);
    int hits = bit_on_bitboard_hit_8_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(1, hits);
}

void test_board_bit_on_bitboard_hit_8_rank_should_return_0_for_bitboard_with_d5_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, D5);
    int hits = bit_on_bitboard_hit_8_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_7_rank_should_return_0_for_empty_bitboard(void)
{
    Bitboard bitboard = 0x0ULL;
    int hits = bit_on_bitboard_hit_7_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_7_rank_should_return_1_for_bitboard_with_d7_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, D7);
    int hits = bit_on_bitboard_hit_7_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(1, hits);
}

void test_board_bit_on_bitboard_hit_7_rank_should_return_0_for_bitboard_with_d6_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, D6);
    int hits = bit_on_bitboard_hit_7_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_1_ranks_should_return_0_for_empty_bitboard(void)
{
    Bitboard bitboard = 0x0ULL;
    int hits = bit_on_bitboard_hit_1_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_1_rank_should_return_1_for_bitboard_with_e1_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, E1);
    int hits = bit_on_bitboard_hit_1_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(1, hits);
}

void test_board_bit_on_bitboard_hit_1_rank_should_return_0_for_bitboard_with_f4_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, F4);
    int hits = bit_on_bitboard_hit_1_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_2_ranks_should_return_0_for_empty_bitboard(void)
{
    Bitboard bitboard = 0x0ULL;
    int hits = bit_on_bitboard_hit_2_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_2_rank_should_return_1_for_bitboard_with_e2_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, E2);
    int hits = bit_on_bitboard_hit_2_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(1, hits);
}

void test_board_bit_on_bitboard_hit_2_rank_should_return_0_for_bitboard_with_f4_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, F4);
    int hits = bit_on_bitboard_hit_2_rank(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_a_file_should_return_0_for_empty_bitboard(void)
{
    Bitboard bitboard = 0x0ULL;
    int hits = bit_on_bitboard_hit_a_file(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_a_file_should_return_1_for_bitboard_with_a5_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, A5);
    int hits = bit_on_bitboard_hit_a_file(bitboard);

    TEST_ASSERT_EQUAL_INT(1, hits);
}

void test_board_bit_on_bitboard_hit_a_file_should_return_0_for_bitboard_with_b5_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, B5);
    int hits = bit_on_bitboard_hit_a_file(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_b_file_should_return_0_for_empty_bitboard(void)
{
    Bitboard bitboard = 0x0ULL;
    int hits = bit_on_bitboard_hit_b_file(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_b_file_should_return_1_for_bitboard_with_b5_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, B5);
    int hits = bit_on_bitboard_hit_b_file(bitboard);

    TEST_ASSERT_EQUAL_INT(1, hits);
}

void test_board_bit_on_bitboard_hit_b_file_should_return_0_for_bitboard_with_f5_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, F5);
    int hits = bit_on_bitboard_hit_b_file(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_h_file_should_return_0_for_empty_bitboard(void)
{
    Bitboard bitboard = 0x0ULL;
    int hits = bit_on_bitboard_hit_h_file(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_h_file_should_return_1_for_bitboard_with_h5_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, H5);
    int hits = bit_on_bitboard_hit_h_file(bitboard);

    TEST_ASSERT_EQUAL_INT(1, hits);
}

void test_board_bit_on_bitboard_hit_h_file_should_return_0_for_bitboard_with_d5_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, D5);
    int hits = bit_on_bitboard_hit_a_file(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_g_file_should_return_0_for_empty_bitboard(void)
{
    Bitboard bitboard = 0x0ULL;
    int hits = bit_on_bitboard_hit_g_file(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

void test_board_bit_on_bitboard_hit_g_file_should_return_1_for_bitboard_with_g5_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, G5);
    int hits = bit_on_bitboard_hit_g_file(bitboard);

    TEST_ASSERT_EQUAL_INT(1, hits);
}

void test_board_bit_on_bitboard_hit_g_file_should_return_0_for_bitboard_with_d5_set(void)
{
    Bitboard bitboard = 0x0ULL;
    bitboard = SET_BIT_ON_BITBOARD(bitboard, D5);
    int hits = bit_on_bitboard_hit_g_file(bitboard);

    TEST_ASSERT_EQUAL_INT(0, hits);
}

#endif // TEST
