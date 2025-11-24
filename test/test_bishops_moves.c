

#ifdef TEST

#include "unity.h"

#include "bishops_moves.h"
#include "board.h"
#include "binary_tools.h"

void setUp(void)
{
    initialize_pre_calculated_bishop_moves_database();
}

void tearDown(void)
{
}

void test_generate_bishop_move_from_a1_without_blocking_piece_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_bishop_moves_from_square_without_blocking_piece(A1);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, B2);
    expected = set_bit_on_bitboard(expected, C3);
    expected = set_bit_on_bitboard(expected, D4);
    expected = set_bit_on_bitboard(expected, E5);
    expected = set_bit_on_bitboard(expected, F6);
    expected = set_bit_on_bitboard(expected, G7);
    expected = set_bit_on_bitboard(expected, H8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_move_from_d4_without_blocking_piece_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_bishop_moves_from_square_without_blocking_piece(D4);
    Bitboard expected = 0x0ULL;

    // Up-right diagonal
    expected = set_bit_on_bitboard(expected, E5);
    expected = set_bit_on_bitboard(expected, F6);
    expected = set_bit_on_bitboard(expected, G7);
    expected = set_bit_on_bitboard(expected, H8);
    
    // Down-left diagonal
    expected = set_bit_on_bitboard(expected, C3);
    expected = set_bit_on_bitboard(expected, B2);
    expected = set_bit_on_bitboard(expected, A1);
    
    // Up-left diagonal
    expected = set_bit_on_bitboard(expected, C5);
    expected = set_bit_on_bitboard(expected, B6);
    expected = set_bit_on_bitboard(expected, A7);
    
    // Down-right diagonal
    expected = set_bit_on_bitboard(expected, E3);
    expected = set_bit_on_bitboard(expected, F2);
    expected = set_bit_on_bitboard(expected, G1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_move_from_b7_without_blocking_piece_edge_remove_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_bishop_moves_from_square_without_blocking_piece_edge_remove(B7);
    Bitboard expected = 0x0ULL;

    // Up-right diagonal: C6, D5, E4, F3, G2
    expected = set_bit_on_bitboard(expected, C6);
    expected = set_bit_on_bitboard(expected, D5);
    expected = set_bit_on_bitboard(expected, E4);
    expected = set_bit_on_bitboard(expected, F3);
    expected = set_bit_on_bitboard(expected, G2);
    
    
    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_move_from_c6_without_blocking_piece_edge_remove_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_bishop_moves_from_square_without_blocking_piece_edge_remove(C6);
    Bitboard expected = 0x0ULL;

    // Up-right diagonal (stops before edge)
    expected = set_bit_on_bitboard(expected, D7);
    
    // Down-left diagonal (stops after edge)
    expected = set_bit_on_bitboard(expected, B5);
    
    // Up-left diagonal (stops before edge)
    expected = set_bit_on_bitboard(expected, B7);
    
    // Down-right diagonal (stops after edge)
    expected = set_bit_on_bitboard(expected, D5);
    expected = set_bit_on_bitboard(expected, E4);
    expected = set_bit_on_bitboard(expected, F3);
    expected = set_bit_on_bitboard(expected, G2);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_move_from_d4_without_blocking_piece_edge_remove_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_bishop_moves_from_square_without_blocking_piece_edge_remove(D4);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, E3);
    expected = set_bit_on_bitboard(expected, F2);
    expected = set_bit_on_bitboard(expected, C5);
    expected = set_bit_on_bitboard(expected, B6);
    expected = set_bit_on_bitboard(expected, C3);
    expected = set_bit_on_bitboard(expected, B2);
    expected = set_bit_on_bitboard(expected, E5);
    expected = set_bit_on_bitboard(expected, F6);
    expected = set_bit_on_bitboard(expected, G7);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_get_bishop_blocker_configuration_for_d4_giving_index_0_should_return_0(void)
{
    Bitboard blockers = get_bishop_blocker_configuration_for_square_giving_index(D4, 0);
    Bitboard expected = 0x0ULL;

    TEST_ASSERT_EQUAL_UINT64(expected, blockers);
}

void test_get_bishop_blocker_configuration_for_c3_giving_index_127_should_return_all_blocker_set(void)
{
    Bitboard blockers = get_bishop_blocker_configuration_for_square_giving_index(C3, 127);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, D4);      
    expected = set_bit_on_bitboard(expected, E5);      
    expected = set_bit_on_bitboard(expected, F6);      
    expected = set_bit_on_bitboard(expected, G7);      
    expected = set_bit_on_bitboard(expected, B2);      
    expected = set_bit_on_bitboard(expected, B4);
    expected = set_bit_on_bitboard(expected, D2);

    TEST_ASSERT_EQUAL_UINT64(expected, blockers);
}

void test_get_bishop_blocker_configuration_for_d4_giving_index_16_should_return_valid_blocker_configuration(void)
{
    Bitboard blockers = get_bishop_blocker_configuration_for_square_giving_index(D4, 16);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, E5);      


    TEST_ASSERT_EQUAL_UINT64(expected, blockers);
}

void test_get_bishop_blocker_configuration_for_c6_giving_index_7_should_return_valid_blocker_configuration(void)
{
    Bitboard blockers = get_bishop_blocker_configuration_for_square_giving_index(C6, 7);
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, D7);
    expected = set_bit_on_bitboard(expected, B5);
    expected = set_bit_on_bitboard(expected, B7);

    TEST_ASSERT_EQUAL_UINT64(expected, blockers);
}

void test_test_candidate_magic_bitboard_bishop_with_known_magic_should_return_1(void)
{
    Bitboard magic_number = 0x800a0040600c0300ULL; 
    int result = test_candidate_magic_bitboard_bishop(C4, magic_number);

    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_test_candidate_magic_bitboard_bishop_with_invalid_magic_should_return_0(void)
{
    Bitboard magic_number = 0x1234567890abcdefULL; 
    int result = test_candidate_magic_bitboard_bishop(C4, magic_number);

    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_generate_magic_number_for_bishop_on_square_should_return_valid_magic_number(void)
{
    Bitboard magic_number = generate_magic_number_for_bishop_on_square(C4);
    
    TEST_ASSERT_EQUAL_INT(1, test_candidate_magic_bitboard_bishop(C4, magic_number));

}

void test_generate_all_magic_numbers_for_bishops_should_return_valid_magic_numbers(void)
{
    Bitboard* magic_numbers = generate_all_magic_numbers_for_bishops();

    for (Square sq = 0; sq < 64; sq++)
    {
        TEST_ASSERT_EQUAL_INT(1, test_candidate_magic_bitboard_bishop(sq, magic_numbers[sq]));
    }
    free(magic_numbers);
}

void test_all_bishops_magic_numbers_constants_should_be_valid(void)
{
    for (Square sq = 0; sq < 64; sq++)
    {
        TEST_ASSERT_EQUAL_INT(1, test_candidate_magic_bitboard_bishop(sq, bishop_magic_numbers[sq]));
    }
}

void test_generate_bishop_moves_on_F6_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x4915815154815ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = generate_bishop_moves_for_giving_blocker_configuration(F6, blockers);
    
    expected = set_bit_on_bitboard(expected, G7);
    expected = set_bit_on_bitboard(expected, E7);
    expected = set_bit_on_bitboard(expected, D8);
    expected = set_bit_on_bitboard(expected, G5);
    expected = set_bit_on_bitboard(expected, H4);
    expected = set_bit_on_bitboard(expected, E5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_moves_on_E7_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x0000000000280010ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = generate_bishop_moves_for_giving_blocker_configuration(E7, blockers);
    
    expected = set_bit_on_bitboard(expected, D8);
    expected = set_bit_on_bitboard(expected, F8);
    expected = set_bit_on_bitboard(expected, D6);
    expected = set_bit_on_bitboard(expected, F6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_moves_on_E7_for_0_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x0000000000000000ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = generate_bishop_moves_for_giving_blocker_configuration(E7, blockers);
    
    expected = set_bit_on_bitboard(expected, D8);
    expected = set_bit_on_bitboard(expected, F8);
    expected = set_bit_on_bitboard(expected, D6);
    expected = set_bit_on_bitboard(expected, C5);
    expected = set_bit_on_bitboard(expected, B4);
    expected = set_bit_on_bitboard(expected, A3);
    expected = set_bit_on_bitboard(expected, F6);
    expected = set_bit_on_bitboard(expected, G5);
    expected = set_bit_on_bitboard(expected, H4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_bishop_moves_on_D7_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x8450684045448ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(D7, blockers);
    
    expected = set_bit_on_bitboard(expected, E8);
    expected = set_bit_on_bitboard(expected, C8);
    expected = set_bit_on_bitboard(expected, C6);
    expected = set_bit_on_bitboard(expected, E6);
    expected = set_bit_on_bitboard(expected, F5);
    expected = set_bit_on_bitboard(expected, G4);
    expected = set_bit_on_bitboard(expected, H3);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_bishop_moves_on_E4_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x8450684045448ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(E4, blockers);

    expected = set_bit_on_bitboard(expected, F5);
    expected = set_bit_on_bitboard(expected, G6);
    expected = set_bit_on_bitboard(expected, H7);
    expected = set_bit_on_bitboard(expected, D5);
    expected = set_bit_on_bitboard(expected, C6);
    expected = set_bit_on_bitboard(expected, D3);
    expected = set_bit_on_bitboard(expected, C2);
    expected = set_bit_on_bitboard(expected, B1);
    expected = set_bit_on_bitboard(expected, F3);
    expected = set_bit_on_bitboard(expected, G2);
    expected = set_bit_on_bitboard(expected, H1);
    
    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}


void test_retrieve_pre_calculated_bishop_moves_on_A1_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x8450684045448ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(A1, blockers);
    
    expected = set_bit_on_bitboard(expected, B2);
    expected = set_bit_on_bitboard(expected, C3);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}


void test_retrieve_pre_calculated_bishop_moves_on_C4_for_0_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x0000000000000000ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(C4, blockers);
    
    expected = set_bit_on_bitboard(expected, D5);
    expected = set_bit_on_bitboard(expected, E6);
    expected = set_bit_on_bitboard(expected, F7);
    expected = set_bit_on_bitboard(expected, G8);
    expected = set_bit_on_bitboard(expected, B5);
    expected = set_bit_on_bitboard(expected, A6);
    expected = set_bit_on_bitboard(expected, B3);
    expected = set_bit_on_bitboard(expected, A2);
    expected = set_bit_on_bitboard(expected, D3);
    expected = set_bit_on_bitboard(expected, E2);
    expected = set_bit_on_bitboard(expected, F1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}



#endif // TEST
