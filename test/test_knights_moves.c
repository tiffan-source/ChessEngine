
// #ifdef TEST

#include "unity.h"

#include "knights_moves.h"
#include "board.h"
#include "moves.h"
#include "game.h"
#include "binary_tools.h"
#include "pieces.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static int compare_move(const void *a, const void *b) {
    int ia = *(const Move*)a;
    int ib = *(const Move*)b;
    return ia - ib;
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

void test_retrieve_pre_calculated_knight_moves_from_h4_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_knight_moves[H4];
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, G6);
    expected = set_bit_on_bitboard(expected, F5);
    expected = set_bit_on_bitboard(expected, F3);
    expected = set_bit_on_bitboard(expected, G2);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_knight_moves_from_g4_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_knight_moves[G4];
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, F6);
    expected = set_bit_on_bitboard(expected, H6);
    expected = set_bit_on_bitboard(expected, F2);
    expected = set_bit_on_bitboard(expected, H2);
    expected = set_bit_on_bitboard(expected, E3);
    expected = set_bit_on_bitboard(expected, E5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_knight_moves_from_h1_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_knight_moves[H1];
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, G3);
    expected = set_bit_on_bitboard(expected, F2);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_knight_moves_from_e4_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_knight_moves[E4];
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, D6);
    expected = set_bit_on_bitboard(expected, F6);
    expected = set_bit_on_bitboard(expected, G5);
    expected = set_bit_on_bitboard(expected, G3);
    expected = set_bit_on_bitboard(expected, F2);
    expected = set_bit_on_bitboard(expected, D2);
    expected = set_bit_on_bitboard(expected, C5);
    expected = set_bit_on_bitboard(expected, C3);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_knight_moves_from_g7_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_knight_moves[G7];
    Bitboard expected = 0x0ULL;

    expected = set_bit_on_bitboard(expected, E8);
    expected = set_bit_on_bitboard(expected, E6);
    expected = set_bit_on_bitboard(expected, F5);
    expected = set_bit_on_bitboard(expected, H5);


    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_all_white_knight_move_from_tricky_position(void)
{
    char* position_white = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K w kq - 0 1";

    Game *game_white = create_game_from_FEN(position_white);

    MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
    result_for_white->current_index = 0;

    Move expected_for_white[] = {
        create_move(F7, D8, WHITE_KNIGHT, QUIET_MOVES),
        create_move(F7, D6, WHITE_KNIGHT, QUIET_MOVES),
        create_move(F7, E5, WHITE_KNIGHT, QUIET_MOVES),
        create_move(F7, G5, WHITE_KNIGHT, QUIET_MOVES),
        create_move(F7, H6, WHITE_KNIGHT, QUIET_MOVES),
        create_move(F7, H8, WHITE_KNIGHT, CAPTURE),

        create_move(F3, D4, WHITE_KNIGHT, QUIET_MOVES),
        create_move(F3, E5, WHITE_KNIGHT, QUIET_MOVES),
        create_move(F3, G5, WHITE_KNIGHT, QUIET_MOVES),
        create_move(F3, H4, WHITE_KNIGHT, QUIET_MOVES),
        create_move(F3, H2, WHITE_KNIGHT, CAPTURE),
        create_move(F3, G1, WHITE_KNIGHT, QUIET_MOVES),
        create_move(F3, E1, WHITE_KNIGHT, QUIET_MOVES),
    };

    generate_all_knight_moves_from_game_state(game_white, result_for_white);


    qsort(result_for_white->moves, result_for_white->current_index, sizeof(Move), compare_move);
    qsort(expected_for_white, 13, sizeof(Move), compare_move);
    
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_for_white, result_for_white->moves, 13);

    free_game(game_white);
    free(result_for_white);

}

void test_generate_all_black_knight_move_from_tricky_position(void)
{
    char* black_position = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K b kq - 0 1";

    Game *game_black = create_game_from_FEN(black_position);

    MoveList* result_for_black = (MoveList*) malloc(sizeof(MoveList));
    result_for_black->current_index = 0;

    Move expected_for_black[] = {
        create_move(F6, D5, BLACK_KNIGHT, QUIET_MOVES),
        create_move(F6, E4, BLACK_KNIGHT, CAPTURE),
        create_move(F6, G4, BLACK_KNIGHT, QUIET_MOVES),
        create_move(F6, H5, BLACK_KNIGHT, QUIET_MOVES),
        create_move(F6, G8, BLACK_KNIGHT, QUIET_MOVES),

        create_move(A5, B3, BLACK_KNIGHT, QUIET_MOVES),
        create_move(A5, C4, BLACK_KNIGHT, CAPTURE),
        create_move(A5, C6, BLACK_KNIGHT, QUIET_MOVES),
    };

    generate_all_knight_moves_from_game_state(game_black, result_for_black);


    qsort(result_for_black->moves, result_for_black->current_index, sizeof(Move), compare_move);
    qsort(expected_for_black, 8, sizeof(Move), compare_move);    
    
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_for_black, result_for_black->moves, 8);

    free_game(game_black);
    free(result_for_black);

}

void test_generate_all_knight_moves_whith_capture(void)
{
    char *position = "rnbqkb1r/pppppppp/5n2/3N4/8/8/PPPPPPPP/R1BQKBNR b KQkq - 3 2";
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    Move expected[] = {
        create_move(F6, G8, BLACK_KNIGHT, QUIET_MOVES),
        create_move(F6, H5, BLACK_KNIGHT, QUIET_MOVES),
        create_move(F6, G4, BLACK_KNIGHT, QUIET_MOVES),
        create_move(F6, E4, BLACK_KNIGHT, QUIET_MOVES),
        create_move(F6, D5, BLACK_KNIGHT, CAPTURE),
        create_move(B8, C6, BLACK_KNIGHT, QUIET_MOVES),
        create_move(B8, A6, BLACK_KNIGHT, QUIET_MOVES),
    };

    generate_all_knight_moves_from_game_state(game, result);

    qsort(result->moves, result->current_index, sizeof(Move), compare_move);
    qsort(expected, 7, sizeof(Move), compare_move);

    TEST_ASSERT_EQUAL_INT(result->current_index, 7);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result->moves, 7);

    free_game(game);
    free(result);
}
// #endif // TEST
