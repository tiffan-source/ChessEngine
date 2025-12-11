
// #ifdef TEST

#include "unity.h"

#include "rooks_moves.h"
#include "board.h"
#include "binary_tools.h"
#include "game.h"
#include "moves.h"
#include "pieces.h"
#include "test_helpers.h"

void setUp(void)
{
    initialize_pre_calculated_rook_moves_database();
}

void tearDown(void)
{
}

void test_generate_rooks_move_from_a1_without_blocking_piece_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_rook_moves_from_square_without_blocking_piece(A1);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, A2);
    expected = SET_BIT_ON_BITBOARD(expected, A3);
    expected = SET_BIT_ON_BITBOARD(expected, A4);
    expected = SET_BIT_ON_BITBOARD(expected, A5);
    expected = SET_BIT_ON_BITBOARD(expected, A6);
    expected = SET_BIT_ON_BITBOARD(expected, A7);
    expected = SET_BIT_ON_BITBOARD(expected, A8);
    expected = SET_BIT_ON_BITBOARD(expected, B1);
    expected = SET_BIT_ON_BITBOARD(expected, C1);
    expected = SET_BIT_ON_BITBOARD(expected, D1);
    expected = SET_BIT_ON_BITBOARD(expected, E1);
    expected = SET_BIT_ON_BITBOARD(expected, F1);
    expected = SET_BIT_ON_BITBOARD(expected, G1);
    expected = SET_BIT_ON_BITBOARD(expected, H1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_rooks_move_from_d4_without_blocking_piece_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_rook_moves_from_square_without_blocking_piece(D4);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, D5);
    expected = SET_BIT_ON_BITBOARD(expected, D6);
    expected = SET_BIT_ON_BITBOARD(expected, D7);
    expected = SET_BIT_ON_BITBOARD(expected, D8);
    expected = SET_BIT_ON_BITBOARD(expected, D3);
    expected = SET_BIT_ON_BITBOARD(expected, D2);
    expected = SET_BIT_ON_BITBOARD(expected, D1);
    expected = SET_BIT_ON_BITBOARD(expected, A4);
    expected = SET_BIT_ON_BITBOARD(expected, B4);
    expected = SET_BIT_ON_BITBOARD(expected, C4);
    expected = SET_BIT_ON_BITBOARD(expected, E4);
    expected = SET_BIT_ON_BITBOARD(expected, F4);
    expected = SET_BIT_ON_BITBOARD(expected, G4);
    expected = SET_BIT_ON_BITBOARD(expected, H4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_rooks_move_from_b7_without_blocking_piece_edge_remove_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_rook_moves_from_square_without_blocking_piece_edge_remove(B7);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, B6);
    expected = SET_BIT_ON_BITBOARD(expected, B5);
    expected = SET_BIT_ON_BITBOARD(expected, B4);
    expected = SET_BIT_ON_BITBOARD(expected, B3);
    expected = SET_BIT_ON_BITBOARD(expected, B2);
    expected = SET_BIT_ON_BITBOARD(expected, C7);
    expected = SET_BIT_ON_BITBOARD(expected, D7);
    expected = SET_BIT_ON_BITBOARD(expected, E7);
    expected = SET_BIT_ON_BITBOARD(expected, F7);
    expected = SET_BIT_ON_BITBOARD(expected, G7);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_rooks_move_from_C6_without_blocking_piece_edge_remove_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_rook_moves_from_square_without_blocking_piece_edge_remove(C6);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, C5);
    expected = SET_BIT_ON_BITBOARD(expected, C4);
    expected = SET_BIT_ON_BITBOARD(expected, C3);
    expected = SET_BIT_ON_BITBOARD(expected, C2);
    expected = SET_BIT_ON_BITBOARD(expected, C7);
    expected = SET_BIT_ON_BITBOARD(expected, B6);
    expected = SET_BIT_ON_BITBOARD(expected, D6);
    expected = SET_BIT_ON_BITBOARD(expected, E6);
    expected = SET_BIT_ON_BITBOARD(expected, F6);
    expected = SET_BIT_ON_BITBOARD(expected, G6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_rooks_move_from_a1_without_blocking_piece_edge_remove_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_rook_moves_from_square_without_blocking_piece_edge_remove(A1);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, A2);
    expected = SET_BIT_ON_BITBOARD(expected, A3);
    expected = SET_BIT_ON_BITBOARD(expected, A4);
    expected = SET_BIT_ON_BITBOARD(expected, A5);
    expected = SET_BIT_ON_BITBOARD(expected, A6);
    expected = SET_BIT_ON_BITBOARD(expected, A7);
    expected = SET_BIT_ON_BITBOARD(expected, B1);
    expected = SET_BIT_ON_BITBOARD(expected, C1);
    expected = SET_BIT_ON_BITBOARD(expected, D1);
    expected = SET_BIT_ON_BITBOARD(expected, E1);
    expected = SET_BIT_ON_BITBOARD(expected, F1);
    expected = SET_BIT_ON_BITBOARD(expected, G1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_get_rook_blocker_configuration_for_d4_giving_index_0_sould_return_0(void)
{
    Bitboard blockers = get_rook_blocker_configuration_for_square_giving_index(D4, 0);
    Bitboard expected = 0x0ULL;

    TEST_ASSERT_EQUAL_UINT64(expected, blockers);
}

void test_get_rook_blocker_configuration_for_g7_giving_index_0_sould_return_0(void)
{
    Bitboard blockers = get_rook_blocker_configuration_for_square_giving_index(G7, 0);
    Bitboard expected = 0x0ULL;

    TEST_ASSERT_EQUAL_UINT64(expected, blockers);
}

void test_get_rook_blocker_configuration_for_e6_giving_index_1023_sould_return_all_blockers_set(void)
{
    Bitboard blockers = get_rook_blocker_configuration_for_square_giving_index(E6, 1023);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, E7);
    expected = SET_BIT_ON_BITBOARD(expected, E5);
    expected = SET_BIT_ON_BITBOARD(expected, E4);
    expected = SET_BIT_ON_BITBOARD(expected, E3);
    expected = SET_BIT_ON_BITBOARD(expected, E2);
    expected = SET_BIT_ON_BITBOARD(expected, B6);
    expected = SET_BIT_ON_BITBOARD(expected, C6);
    expected = SET_BIT_ON_BITBOARD(expected, D6);
    expected = SET_BIT_ON_BITBOARD(expected, F6);
    expected = SET_BIT_ON_BITBOARD(expected, G6);

    TEST_ASSERT_EQUAL_UINT64(expected, blockers);
}

void test_get_rook_blocker_configuration_for_b4_giving_index_3_sould_return_valid_blocker_configuration(void)
{
    Bitboard blockers = get_rook_blocker_configuration_for_square_giving_index(B4, 3);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, B7);
    expected = SET_BIT_ON_BITBOARD(expected, B6);

    TEST_ASSERT_EQUAL_UINT64(expected, blockers);
}

void test_test_candidate_magic_bitboard_rook_with_known_magic_number_should_return_valid_result(void)
{
    Bitboard magic_number1 = 0x4080002080104000ULL;
    int test_result1 = test_candidate_magic_bitboard_rook(A8, magic_number1);

    Bitboard magic_number2 = 0x82020040a08011ULL;
    int test_result2 = test_candidate_magic_bitboard_rook(C6, magic_number2);

    Bitboard magic_number3 = 0xc012001008120084ULL;
    int test_result3 = test_candidate_magic_bitboard_rook(F3, magic_number3);

    Bitboard magic_number4 = 0xc1080011000c4900ULL;
    int test_result4 = test_candidate_magic_bitboard_rook(E2, magic_number4);

    Bitboard magic_number5 = 0x408200050044ULL;
    int test_result5 = test_candidate_magic_bitboard_rook(H5, magic_number5);

    TEST_ASSERT_EQUAL_INT(1, test_result1);
    TEST_ASSERT_EQUAL_INT(1, test_result2);
    TEST_ASSERT_EQUAL_INT(1, test_result3);
    TEST_ASSERT_EQUAL_INT(1, test_result4);
    TEST_ASSERT_EQUAL_INT(1, test_result5);
}

void test_test_candidate_magic_bitboard_rook_with_invalid_magic_number_should_return_zero(void)
{
    Bitboard invalid_magic_number1 = 0x1234567890abcdefULL;
    int test_result1 = test_candidate_magic_bitboard_rook(D4, invalid_magic_number1);

    Bitboard invalid_magic_number2 = 0xffffffffffffffffULL;
    int test_result2 = test_candidate_magic_bitboard_rook(B2, invalid_magic_number2);

    TEST_ASSERT_EQUAL_INT(0, test_result1);
    TEST_ASSERT_EQUAL_INT(0, test_result2);
}

void test_generate_magic_number_for_rook_on_square_should_return_valid_magic_number(void)
{
    Bitboard magic_number = generate_magic_number_for_rook_on_square(A8);
    
    TEST_ASSERT_EQUAL_INT(1, test_candidate_magic_bitboard_rook(A8, magic_number));

}

void test_generate_all_magic_numbers_for_rooks_should_return_valid_magic_numbers(void)
{
    Bitboard* magic_numbers = generate_all_magic_numbers_for_rooks();
    int i;
    int test_result;

    for (i = 0; i < 64; i++)
    {
        test_result = test_candidate_magic_bitboard_rook((Square)i, magic_numbers[i]);
        TEST_ASSERT_EQUAL_INT(1, test_result);
    }

    free(magic_numbers);
}

void test_all_rooks_magic_numbers_should_be_valid(void)
{
    int i;
    int test_result;

    for (i = 0; i < 64; i++)
    {
        test_result = test_candidate_magic_bitboard_rook((Square)i, rook_magic_numbers[i]);
        TEST_ASSERT_EQUAL_INT(1, test_result);
    }
}

void test_generate_rook_moves_on_E6_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x0000000000280010ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = generate_rook_moves_for_giving_blocker_configuration(E6, blockers);
    
    expected = SET_BIT_ON_BITBOARD(expected, E7);
    expected = SET_BIT_ON_BITBOARD(expected, E8);
    expected = SET_BIT_ON_BITBOARD(expected, E5);
    expected = SET_BIT_ON_BITBOARD(expected, E4);
    expected = SET_BIT_ON_BITBOARD(expected, E3);
    expected = SET_BIT_ON_BITBOARD(expected, E2);
    expected = SET_BIT_ON_BITBOARD(expected, E1);
    expected = SET_BIT_ON_BITBOARD(expected, D6);
    expected = SET_BIT_ON_BITBOARD(expected, F6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_rook_moves_on_H6_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x0000000000380030ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = generate_rook_moves_for_giving_blocker_configuration(H6, blockers);
    
    expected = SET_BIT_ON_BITBOARD(expected, H7);
    expected = SET_BIT_ON_BITBOARD(expected, H8);
    expected = SET_BIT_ON_BITBOARD(expected, H5);
    expected = SET_BIT_ON_BITBOARD(expected, H4);
    expected = SET_BIT_ON_BITBOARD(expected, H3);
    expected = SET_BIT_ON_BITBOARD(expected, H2);
    expected = SET_BIT_ON_BITBOARD(expected, H1);
    expected = SET_BIT_ON_BITBOARD(expected, G6);
    expected = SET_BIT_ON_BITBOARD(expected, F6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_rook_moves_on_H6_for_0_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x0000000000000000ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = generate_rook_moves_for_giving_blocker_configuration(H6, blockers);
    
    expected = SET_BIT_ON_BITBOARD(expected, H7);
    expected = SET_BIT_ON_BITBOARD(expected, H8);
    expected = SET_BIT_ON_BITBOARD(expected, H5);
    expected = SET_BIT_ON_BITBOARD(expected, H4);
    expected = SET_BIT_ON_BITBOARD(expected, H3);
    expected = SET_BIT_ON_BITBOARD(expected, H2);
    expected = SET_BIT_ON_BITBOARD(expected, H1);
    expected = SET_BIT_ON_BITBOARD(expected, G6);
    expected = SET_BIT_ON_BITBOARD(expected, F6);
    expected = SET_BIT_ON_BITBOARD(expected, E6);
    expected = SET_BIT_ON_BITBOARD(expected, D6);
    expected = SET_BIT_ON_BITBOARD(expected, C6);
    expected = SET_BIT_ON_BITBOARD(expected, B6);
    expected = SET_BIT_ON_BITBOARD(expected, A6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_rook_moves_on_D7_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x8450684045448ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(D7, blockers);
    
    expected = SET_BIT_ON_BITBOARD(expected, D8);
    expected = SET_BIT_ON_BITBOARD(expected, D6);
    expected = SET_BIT_ON_BITBOARD(expected, D5);
    expected = SET_BIT_ON_BITBOARD(expected, D4);
    expected = SET_BIT_ON_BITBOARD(expected, D3);
    expected = SET_BIT_ON_BITBOARD(expected, D2);
    expected = SET_BIT_ON_BITBOARD(expected, C7);
    expected = SET_BIT_ON_BITBOARD(expected, E7);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_rook_moves_on_E4_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x8450684045448ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(E4, blockers);

    expected = SET_BIT_ON_BITBOARD(expected, E5);
    expected = SET_BIT_ON_BITBOARD(expected, E6);
    expected = SET_BIT_ON_BITBOARD(expected, E7);
    expected = SET_BIT_ON_BITBOARD(expected, E3);
    expected = SET_BIT_ON_BITBOARD(expected, E2);
    expected = SET_BIT_ON_BITBOARD(expected, E1);
    expected = SET_BIT_ON_BITBOARD(expected, D4);
    expected = SET_BIT_ON_BITBOARD(expected, C4);
    expected = SET_BIT_ON_BITBOARD(expected, F4);
    expected = SET_BIT_ON_BITBOARD(expected, G4);
    expected = SET_BIT_ON_BITBOARD(expected, H4);
    
    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}


void test_retrieve_pre_calculated_rook_moves_on_A1_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x8450684045448ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(A1, blockers);
    
    expected = SET_BIT_ON_BITBOARD(expected, A2);
    expected = SET_BIT_ON_BITBOARD(expected, A3);
    expected = SET_BIT_ON_BITBOARD(expected, B1);
    expected = SET_BIT_ON_BITBOARD(expected, C1);
    expected = SET_BIT_ON_BITBOARD(expected, D1);
    expected = SET_BIT_ON_BITBOARD(expected, E1);
    expected = SET_BIT_ON_BITBOARD(expected, F1);
    expected = SET_BIT_ON_BITBOARD(expected, G1);
    expected = SET_BIT_ON_BITBOARD(expected, H1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_rook_moves_on_C4_for_0_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x0000000000000000ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(C4, blockers);
    
    expected = SET_BIT_ON_BITBOARD(expected, C5);
    expected = SET_BIT_ON_BITBOARD(expected, C6);
    expected = SET_BIT_ON_BITBOARD(expected, C7);
    expected = SET_BIT_ON_BITBOARD(expected, C8);
    expected = SET_BIT_ON_BITBOARD(expected, C3);
    expected = SET_BIT_ON_BITBOARD(expected, C2);
    expected = SET_BIT_ON_BITBOARD(expected, C1);
    expected = SET_BIT_ON_BITBOARD(expected, B4);
    expected = SET_BIT_ON_BITBOARD(expected, A4);
    expected = SET_BIT_ON_BITBOARD(expected, D4);
    expected = SET_BIT_ON_BITBOARD(expected, E4);
    expected = SET_BIT_ON_BITBOARD(expected, F4);
    expected = SET_BIT_ON_BITBOARD(expected, G4);
    expected = SET_BIT_ON_BITBOARD(expected, H4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_rook_moves_on_59_for_a9cb21170362ef91_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0xa9cb21170362ef91ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(59, blockers);

    expected = SET_BIT_ON_BITBOARD(expected, D2);
    expected = SET_BIT_ON_BITBOARD(expected, C1);
    expected = SET_BIT_ON_BITBOARD(expected, B1);
    expected = SET_BIT_ON_BITBOARD(expected, A1);
    expected = SET_BIT_ON_BITBOARD(expected, E1);
    expected = SET_BIT_ON_BITBOARD(expected, F1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_all_white_rook_move_from_tricky_position(void)
{
    char *position_white = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K w kq - 0 1";
    
    Game *game_white = create_game_from_FEN(position_white);

    MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
    result_for_white->current_index = 0;

    ScoredMove expected_for_white[] = {
        CREATE_SCORED_MOVE(A1, B1, WHITE_ROOK, QUIET_MOVES),
        CREATE_SCORED_MOVE(A1, C1, WHITE_ROOK, QUIET_MOVES),
        CREATE_SCORED_MOVE(F1, E1, WHITE_ROOK, QUIET_MOVES),
        CREATE_SCORED_MOVE(F1, G1, WHITE_ROOK, QUIET_MOVES),
        CREATE_SCORED_MOVE(F1, F2, WHITE_ROOK, QUIET_MOVES),
    };
    
    generate_all_rooks_moves_from_game_state(game_white, result_for_white);

    qsort(result_for_white->moves, result_for_white->current_index, sizeof(ScoredMove), test_helper_compare_scored_move);
    qsort(expected_for_white, 5, sizeof(ScoredMove), test_helper_compare_scored_move);    

    TEST_ASSERT_EQUAL_INT(5, result_for_white->current_index);
    assert_move_lists_equal(expected_for_white, result_for_white->moves, 5);

    free_game(game_white);
    free(result_for_white);
}

void test_generate_all_black_rook_move_from_tricky_position(void)
{
    char *position_black = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K b kq - 0 1";

    Game *game_black = create_game_from_FEN(position_black);

    MoveList* result_for_black = (MoveList*) malloc(sizeof(MoveList));
    result_for_black->current_index = 0;

    ScoredMove expected_for_black[] = {
        CREATE_SCORED_MOVE(A8, B8, BLACK_ROOK, QUIET_MOVES),
        CREATE_SCORED_MOVE(A8, C8, BLACK_ROOK, QUIET_MOVES),
        CREATE_SCORED_MOVE(A8, D8, BLACK_ROOK, QUIET_MOVES),
        CREATE_SCORED_MOVE(A8, A7, BLACK_ROOK, CAPTURE),
        CREATE_SCORED_MOVE(H8, G8, BLACK_ROOK, QUIET_MOVES),
        CREATE_SCORED_MOVE(H8, F8, BLACK_ROOK, QUIET_MOVES),
    };
    
    generate_all_rooks_moves_from_game_state(game_black, result_for_black);
    
    qsort(result_for_black->moves, result_for_black->current_index, sizeof(ScoredMove), test_helper_compare_scored_move);
    qsort(expected_for_black, 6, sizeof(ScoredMove), test_helper_compare_scored_move);

    TEST_ASSERT_EQUAL_INT(6, result_for_black->current_index);
    assert_move_lists_equal(expected_for_black, result_for_black->moves, 6);

    free_game(game_black);
    free(result_for_black);
}

void test_generate_all_white_rooks_capture_from_tricky_position(void)
{
    char *position_white = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
    
    Game *game_white = create_game_from_FEN(position_white);

    MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
    result_for_white->current_index = 0;

    ScoredMove expected_for_white[] = {
        CREATE_SCORED_MOVE(B4, F4, WHITE_ROOK, CAPTURE)
    };
    
    generate_all_rooks_captures_from_game_state(game_white, result_for_white);   

    TEST_ASSERT_EQUAL_UINT(1, result_for_white->current_index);
    assert_move_lists_equal(expected_for_white, result_for_white->moves, 1);

    free_game(game_white);
    free(result_for_white);

}

void test_generate_all_black_rooks_capture_from_tricky_position(void)
{
    char *position_black = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 b - - 0 1";

    Game *game_black = create_game_from_FEN(position_black);

    MoveList* result_for_black = (MoveList*) malloc(sizeof(MoveList));
    result_for_black->current_index = 0;

    ScoredMove expected_for_black[] = {
        CREATE_SCORED_MOVE(H5, B5, BLACK_ROOK, CAPTURE)
    };
    
    generate_all_rooks_captures_from_game_state(game_black, result_for_black);
    
    TEST_ASSERT_EQUAL_UINT(1, result_for_black->current_index);
    assert_move_lists_equal(expected_for_black, result_for_black->moves, 1);
    free_game(game_black);

    free(result_for_black);
}
// #endif // TEST
