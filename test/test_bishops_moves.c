
// #ifdef TEST

#include "unity.h"

#include "bishops_moves.h"
#include "board.h"
#include "binary_tools.h"
#include "game.h"
#include "moves.h"
#include "pieces.h"

void setUp(void)
{
    initialize_pre_calculated_bishop_moves_database();
}

void tearDown(void)
{
}

static int compare_move(const void *a, const void *b) {
    int ia = *(const Move*)a;
    int ib = *(const Move*)b;
    return ia - ib;
}

void test_generate_bishop_move_from_a1_without_blocking_piece_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_bishop_moves_from_square_without_blocking_piece(A1);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, B2);
    expected = SET_BIT_ON_BITBOARD(expected, C3);
    expected = SET_BIT_ON_BITBOARD(expected, D4);
    expected = SET_BIT_ON_BITBOARD(expected, E5);
    expected = SET_BIT_ON_BITBOARD(expected, F6);
    expected = SET_BIT_ON_BITBOARD(expected, G7);
    expected = SET_BIT_ON_BITBOARD(expected, H8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_move_from_d4_without_blocking_piece_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_bishop_moves_from_square_without_blocking_piece(D4);
    Bitboard expected = 0x0ULL;

    // Up-right diagonal
    expected = SET_BIT_ON_BITBOARD(expected, E5);
    expected = SET_BIT_ON_BITBOARD(expected, F6);
    expected = SET_BIT_ON_BITBOARD(expected, G7);
    expected = SET_BIT_ON_BITBOARD(expected, H8);
    
    // Down-left diagonal
    expected = SET_BIT_ON_BITBOARD(expected, C3);
    expected = SET_BIT_ON_BITBOARD(expected, B2);
    expected = SET_BIT_ON_BITBOARD(expected, A1);
    
    // Up-left diagonal
    expected = SET_BIT_ON_BITBOARD(expected, C5);
    expected = SET_BIT_ON_BITBOARD(expected, B6);
    expected = SET_BIT_ON_BITBOARD(expected, A7);
    
    // Down-right diagonal
    expected = SET_BIT_ON_BITBOARD(expected, E3);
    expected = SET_BIT_ON_BITBOARD(expected, F2);
    expected = SET_BIT_ON_BITBOARD(expected, G1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_move_from_b7_without_blocking_piece_edge_remove_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_bishop_moves_from_square_without_blocking_piece_edge_remove(B7);
    Bitboard expected = 0x0ULL;

    // Up-right diagonal: C6, D5, E4, F3, G2
    expected = SET_BIT_ON_BITBOARD(expected, C6);
    expected = SET_BIT_ON_BITBOARD(expected, D5);
    expected = SET_BIT_ON_BITBOARD(expected, E4);
    expected = SET_BIT_ON_BITBOARD(expected, F3);
    expected = SET_BIT_ON_BITBOARD(expected, G2);
    
    
    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_move_from_c6_without_blocking_piece_edge_remove_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_bishop_moves_from_square_without_blocking_piece_edge_remove(C6);
    Bitboard expected = 0x0ULL;

    // Up-right diagonal (stops before edge)
    expected = SET_BIT_ON_BITBOARD(expected, D7);
    
    // Down-left diagonal (stops after edge)
    expected = SET_BIT_ON_BITBOARD(expected, B5);
    
    // Up-left diagonal (stops before edge)
    expected = SET_BIT_ON_BITBOARD(expected, B7);
    
    // Down-right diagonal (stops after edge)
    expected = SET_BIT_ON_BITBOARD(expected, D5);
    expected = SET_BIT_ON_BITBOARD(expected, E4);
    expected = SET_BIT_ON_BITBOARD(expected, F3);
    expected = SET_BIT_ON_BITBOARD(expected, G2);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_move_from_d4_without_blocking_piece_edge_remove_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_bishop_moves_from_square_without_blocking_piece_edge_remove(D4);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, E3);
    expected = SET_BIT_ON_BITBOARD(expected, F2);
    expected = SET_BIT_ON_BITBOARD(expected, C5);
    expected = SET_BIT_ON_BITBOARD(expected, B6);
    expected = SET_BIT_ON_BITBOARD(expected, C3);
    expected = SET_BIT_ON_BITBOARD(expected, B2);
    expected = SET_BIT_ON_BITBOARD(expected, E5);
    expected = SET_BIT_ON_BITBOARD(expected, F6);
    expected = SET_BIT_ON_BITBOARD(expected, G7);

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

    expected = SET_BIT_ON_BITBOARD(expected, D4);      
    expected = SET_BIT_ON_BITBOARD(expected, E5);      
    expected = SET_BIT_ON_BITBOARD(expected, F6);      
    expected = SET_BIT_ON_BITBOARD(expected, G7);      
    expected = SET_BIT_ON_BITBOARD(expected, B2);      
    expected = SET_BIT_ON_BITBOARD(expected, B4);
    expected = SET_BIT_ON_BITBOARD(expected, D2);

    TEST_ASSERT_EQUAL_UINT64(expected, blockers);
}

void test_get_bishop_blocker_configuration_for_d4_giving_index_16_should_return_valid_blocker_configuration(void)
{
    Bitboard blockers = get_bishop_blocker_configuration_for_square_giving_index(D4, 16);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, E5);      


    TEST_ASSERT_EQUAL_UINT64(expected, blockers);
}

void test_get_bishop_blocker_configuration_for_c6_giving_index_7_should_return_valid_blocker_configuration(void)
{
    Bitboard blockers = get_bishop_blocker_configuration_for_square_giving_index(C6, 7);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, D7);
    expected = SET_BIT_ON_BITBOARD(expected, B5);
    expected = SET_BIT_ON_BITBOARD(expected, B7);

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
    
    expected = SET_BIT_ON_BITBOARD(expected, G7);
    expected = SET_BIT_ON_BITBOARD(expected, E7);
    expected = SET_BIT_ON_BITBOARD(expected, D8);
    expected = SET_BIT_ON_BITBOARD(expected, G5);
    expected = SET_BIT_ON_BITBOARD(expected, H4);
    expected = SET_BIT_ON_BITBOARD(expected, E5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_bishop_moves_on_E7_for_giving_blocker_configuration_should_return_valid_moves(void)
{
    Bitboard blockers = 0x0000000000280010ULL;
    Bitboard expected = 0x0ULL;
    Bitboard moves = generate_bishop_moves_for_giving_blocker_configuration(E7, blockers);
    
    expected = SET_BIT_ON_BITBOARD(expected, D8);
    expected = SET_BIT_ON_BITBOARD(expected, F8);
    expected = SET_BIT_ON_BITBOARD(expected, D6);
    expected = SET_BIT_ON_BITBOARD(expected, F6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_all_white_bishop_move_from_tricky_position(void)
{
    char *position_white = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K w kq - 0 1";
    
    Game *game_white = create_game_from_FEN(position_white);

    MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
    result_for_white->current_index = 0;

    Move expected_for_white[] = {
        CREATE_MOVE(A4, B3, WHITE_BISHOP, QUIET_MOVES),
        CREATE_MOVE(A4, C2, WHITE_BISHOP, QUIET_MOVES),

        CREATE_MOVE(B4, A3, WHITE_BISHOP, CAPTURE),
        CREATE_MOVE(B4, A5, WHITE_BISHOP, CAPTURE),
        CREATE_MOVE(B4, C3, WHITE_BISHOP, QUIET_MOVES),
        CREATE_MOVE(B4, C5, WHITE_BISHOP, QUIET_MOVES),
        CREATE_MOVE(B4, D6, WHITE_BISHOP, QUIET_MOVES),
        CREATE_MOVE(B4, E7, WHITE_BISHOP, QUIET_MOVES),
        CREATE_MOVE(B4, F8, WHITE_BISHOP, QUIET_MOVES),
    };
    
    generate_all_bishop_moves_from_game_state(game_white, result_for_white);

    qsort(result_for_white->moves, result_for_white->current_index, sizeof(Move), compare_move);
    qsort(expected_for_white, 9, sizeof(Move), compare_move);    

    TEST_ASSERT_EQUAL_INT_ARRAY(expected_for_white, result_for_white->moves, 9);

    free_game(game_white);
    free(result_for_white);
}

void test_generate_all_black_bishop_move_from_tricky_position(void)
{
    char *position_black = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K b kq - 0 1";

    Game *game_black = create_game_from_FEN(position_black);

    MoveList* result_for_black = (MoveList*) malloc(sizeof(MoveList));
    result_for_black->current_index = 0;

    Move expected_for_black[] = {
        CREATE_MOVE(B6, C5, BLACK_BISHOP, QUIET_MOVES),
        CREATE_MOVE(B6, D4, BLACK_BISHOP, QUIET_MOVES),
        CREATE_MOVE(B6, E3, BLACK_BISHOP, QUIET_MOVES),
        CREATE_MOVE(B6, F2, BLACK_BISHOP, QUIET_MOVES),
        CREATE_MOVE(B6, G1, BLACK_BISHOP, QUIET_MOVES),
        CREATE_MOVE(B6, A7, BLACK_BISHOP, CAPTURE),

        CREATE_MOVE(G6, F7, BLACK_BISHOP, CAPTURE),
        CREATE_MOVE(G6, F5, BLACK_BISHOP, QUIET_MOVES),
        CREATE_MOVE(G6, E4, BLACK_BISHOP, CAPTURE),
        CREATE_MOVE(G6, H5, BLACK_BISHOP, QUIET_MOVES),
    };
    
    generate_all_bishop_moves_from_game_state(game_black, result_for_black);
    
    qsort(result_for_black->moves, result_for_black->current_index, sizeof(Move), compare_move);
    qsort(expected_for_black, 10, sizeof(Move), compare_move);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected_for_black, result_for_black->moves, 10);
    free_game(game_black);

    free(result_for_black);
}

// #endif // TEST
