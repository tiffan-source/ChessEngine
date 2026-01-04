

#include "unity.h"

#include "zobrist_key.h"
#include "binary_tools.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_initialize_magic_zobrist_numbers_should_set_different_values(void)
{
    initialize_magic_zobrist_numbers();

    // Vérifier que quelques valeurs spécifiques ne sont pas nulles
    TEST_ASSERT_TRUE(0 != pawn_zobrist_magic_number[1][36]);
    TEST_ASSERT_TRUE(0 != knight_zobrist_magic_number[0][62]);
    TEST_ASSERT_TRUE(0 != bishop_zobrist_magic_number[1][2]);
    TEST_ASSERT_TRUE(0 != rook_zobrist_magic_number[0][56]);
    TEST_ASSERT_TRUE(0 != queen_zobrist_magic_number[1][3]);
    TEST_ASSERT_TRUE(0 != king_zobrist_magic_number[0][60]);
    TEST_ASSERT_TRUE(0 != black_to_move_zobrist_magic_number);
    TEST_ASSERT_TRUE(0 != castling_rights_zobrist_magic_number[0]);
    TEST_ASSERT_TRUE(0 != en_passant_square_zobrist_magic_number[28]);
}