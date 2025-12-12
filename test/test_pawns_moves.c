
// #ifdef TEST

#include "unity.h"

#include "pawns_moves.h"
#include "moves.h"
#include "board.h"
#include "game.h"
#include "binary_tools.h"
#include "pieces.h"
#include "test_helpers.h"

void setUp(void)
{
    initialize_pre_calculated_pawn_attacks_database();
    initialize_pre_calculated_pawn_moves_database();
}

void tearDown(void)
{
}


void test_generate_pawns_quiet_moves_from_square_a2_for_white(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(WHITE, A2);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, A3);
    expected = SET_BIT_ON_BITBOARD(expected, A4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_quiet_moves_from_square_b3_for_white(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(WHITE, B3);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, B4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_quiet_moves_from_square_g7_for_white(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(WHITE, G7);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, G8);

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

    expected = SET_BIT_ON_BITBOARD(expected, A6);
    expected = SET_BIT_ON_BITBOARD(expected, A5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_quiet_moves_from_square_d5_for_black(void)
{
    Bitboard moves = generate_pawns_quiet_moves_from_square(BLACK, D5);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, D4);

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

    expected = SET_BIT_ON_BITBOARD(expected, C1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}



void test_generate_pawns_capture_moves_from_square_e3_for_white(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(WHITE, E3);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, D4);
    expected = SET_BIT_ON_BITBOARD(expected, F4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_a7_for_white(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(WHITE, A7);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, B8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_h4_for_white(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(WHITE, H4);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, G5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_c5_for_white(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(WHITE, C5);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, B6);
    expected = SET_BIT_ON_BITBOARD(expected, D6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_h7_for_black(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(BLACK, H7);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, G6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_b2_for_black(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(BLACK, B2);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, A1);
    expected = SET_BIT_ON_BITBOARD(expected, C1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_f6_for_black(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(BLACK, F6);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, E5);
    expected = SET_BIT_ON_BITBOARD(expected, G5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_pawns_capture_moves_from_square_a5_for_black(void)
{
    Bitboard moves = generate_pawns_capture_moves_from_square(BLACK, A5);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, B4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_pawn_moves_for_white_from_e4_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_pawn_moves[WHITE][E4];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, E5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_pawn_moves_for_black_from_d5_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_pawn_moves[BLACK][D5];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, D4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}


void test_retrieve_pre_calculated_pawn_moves_for_white_from_a2_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_pawn_moves[WHITE][A2];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, A3);
    expected = SET_BIT_ON_BITBOARD(expected, A4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_pawn_moves_for_black_from_g7_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_pawn_moves[BLACK][G7];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, G6);
    expected = SET_BIT_ON_BITBOARD(expected, G5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_pawn_attacks_for_white_from_c3_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_pawn_attacks[WHITE][C3];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, B4);
    expected = SET_BIT_ON_BITBOARD(expected, D4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_pawn_attacks_for_black_from_f6_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_pawn_attacks[BLACK][F6];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, E5);
    expected = SET_BIT_ON_BITBOARD(expected, G5);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_pawn_attacks_for_white_from_h7_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_pawn_attacks[WHITE][H7];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, G8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_pawn_attacks_for_black_from_a2_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_pawn_attacks[BLACK][A2];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, B1);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_all_type_white_pawn_move_from_tricky_position(void)
{
    char *position_white = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
    
    Game *game_white = create_game_from_FEN(position_white);

    MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
    result_for_white->current_index = 0;

    ScoredMove expected_for_white[] = {
        CREATE_SCORED_MOVE(C4, C5, WHITE_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(D2, D3, WHITE_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(D2, D4, WHITE_PAWN, DOUBLE_PAWN_PUSH),
        CREATE_SCORED_MOVE(E4, E5, WHITE_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(G2, G3, WHITE_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(G2, G4, WHITE_PAWN, DOUBLE_PAWN_PUSH),
        CREATE_SCORED_MOVE(H2, H3, WHITE_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(H2, H4, WHITE_PAWN, DOUBLE_PAWN_PUSH),
    };
    
    generate_all_white_pawns_moves_from_game_state(game_white, result_for_white);

    qsort(result_for_white->moves, result_for_white->current_index, sizeof(ScoredMove), test_helper_compare_scored_move);
    qsort(expected_for_white, 8, sizeof(ScoredMove), test_helper_compare_scored_move);    

    TEST_ASSERT_EQUAL_INT(8, result_for_white->current_index);
    assert_move_lists_equal(expected_for_white, result_for_white->moves, 8);

    free_game(game_white);
    free(result_for_white);
}


void test_generate_all_type_black_pawn_move_from_tricky_position(void)
{
    char *position_black = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 b kq - 0 1";
    
    Game *game_black = create_game_from_FEN(position_black);

    MoveList* result_for_black = (MoveList*) malloc(sizeof(MoveList));
    result_for_black->current_index = 0;


    ScoredMove expected_for_black[] = {
        CREATE_SCORED_MOVE(B2, B1, BLACK_PAWN, QUEEN_PROMOTION),
        CREATE_SCORED_MOVE(B2, B1, BLACK_PAWN, ROOK_PROMOTION),
        CREATE_SCORED_MOVE(B2, B1, BLACK_PAWN, BISHOP_PROMOTION),
        CREATE_SCORED_MOVE(B2, B1, BLACK_PAWN, KNIGHT_PROMOTION),
        CREATE_SCORED_MOVE(B2, A1, BLACK_PAWN, QUEEN_PROMOTION_CAPTURE),
        CREATE_SCORED_MOVE(B2, A1, BLACK_PAWN, ROOK_PROMOTION_CAPTURE),
        CREATE_SCORED_MOVE(B2, A1, BLACK_PAWN, BISHOP_PROMOTION_CAPTURE),
        CREATE_SCORED_MOVE(B2, A1, BLACK_PAWN, KNIGHT_PROMOTION_CAPTURE),

        CREATE_SCORED_MOVE(C7, C6, BLACK_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(C7, C5, BLACK_PAWN, DOUBLE_PAWN_PUSH),

        CREATE_SCORED_MOVE(D7, D6, BLACK_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(D7, D5, BLACK_PAWN, DOUBLE_PAWN_PUSH),

        CREATE_SCORED_MOVE(G7, H6, BLACK_PAWN, CAPTURE),
    };
    
    generate_all_black_pawns_moves_from_game_state(game_black, result_for_black);
    
    qsort(result_for_black->moves, result_for_black->current_index, sizeof(ScoredMove), test_helper_compare_scored_move);
    qsort(expected_for_black, 13, sizeof(ScoredMove), test_helper_compare_scored_move);

    TEST_ASSERT_EQUAL_INT(13, result_for_black->current_index);
    assert_move_lists_equal(expected_for_black, result_for_black->moves, 13);

    free_game(game_black);

    free(result_for_black);
}

void test_generate_all_pawns_move_from_position_whith_en_passant_for_white(void)
{
    char *position_white = "rnbqkbnr/pppp1pp1/7p/3Pp3/8/8/8/RNBQKBNR w KQkq e6 0 3";

        
    Game *game_white = create_game_from_FEN(position_white);

    MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
    result_for_white->current_index = 0;

    ScoredMove expected_for_white[] = {
        CREATE_SCORED_MOVE(D5, E6, WHITE_PAWN, EN_PASSANT_CAPTURE),
        CREATE_SCORED_MOVE(D5, D6, WHITE_PAWN, QUIET_MOVES),
    };
    
    generate_all_white_pawns_moves_from_game_state(game_white, result_for_white);

    qsort(result_for_white->moves, result_for_white->current_index, sizeof(ScoredMove), test_helper_compare_scored_move);
    qsort(expected_for_white, 2, sizeof(ScoredMove), test_helper_compare_scored_move);    

    TEST_ASSERT_EQUAL_INT(2, result_for_white->current_index);
    assert_move_lists_equal(expected_for_white, result_for_white->moves, 2);

    free_game(game_white);
    free(result_for_white);
}

void test_generate_all_pawns_move_from_position_without_en_passant(void)
{
    char *position = "rnbqkbnr/ppppppp1/8/7p/PP6/8/2PPPPPP/RNBQKBNR b KQkq a3 0 2";
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    ScoredMove expected[] = {
        CREATE_SCORED_MOVE(A7, A6, BLACK_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(A7, A5, BLACK_PAWN, DOUBLE_PAWN_PUSH),
        CREATE_SCORED_MOVE(B7, B6, BLACK_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(B7, B5, BLACK_PAWN, DOUBLE_PAWN_PUSH),
        CREATE_SCORED_MOVE(C7, C6, BLACK_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(C7, C5, BLACK_PAWN, DOUBLE_PAWN_PUSH),
        CREATE_SCORED_MOVE(D7, D6, BLACK_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(D7, D5, BLACK_PAWN, DOUBLE_PAWN_PUSH),
        CREATE_SCORED_MOVE(E7, E6, BLACK_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(E7, E5, BLACK_PAWN, DOUBLE_PAWN_PUSH),
        CREATE_SCORED_MOVE(F7, F6, BLACK_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(F7, F5, BLACK_PAWN, DOUBLE_PAWN_PUSH),
        CREATE_SCORED_MOVE(G7, G6, BLACK_PAWN, QUIET_MOVES),
        CREATE_SCORED_MOVE(G7, G5, BLACK_PAWN, DOUBLE_PAWN_PUSH),
        CREATE_SCORED_MOVE(H5, H4, BLACK_PAWN, QUIET_MOVES),
    };

    generate_all_black_pawns_moves_from_game_state(game, result);

    qsort(result->moves, result->current_index, sizeof(ScoredMove), test_helper_compare_scored_move);
    qsort(expected, 15, sizeof(ScoredMove), test_helper_compare_scored_move);

    TEST_ASSERT_EQUAL_INT(15, result->current_index);
    assert_move_lists_equal(expected, result->moves, 15);

    free_game(game);
    free(result);
}

void test_generate_all_pawns_move_from_position_whith_en_passant_for_black(void)
{
    char *position_black = "rnbqkbnr/8/8/7P/3pP3/8/PPPP1PP1/RNBQKBNR b KQkq e3 0 3";
        
    Game *game_black = create_game_from_FEN(position_black);

    MoveList* result_for_black = (MoveList*) malloc(sizeof(MoveList));
    result_for_black->current_index = 0;

    ScoredMove expected_for_black[] = {
        CREATE_SCORED_MOVE(D4, E3, BLACK_PAWN, EN_PASSANT_CAPTURE),
        CREATE_SCORED_MOVE(D4, D3, BLACK_PAWN, QUIET_MOVES),
    };
    
    generate_all_black_pawns_moves_from_game_state(game_black, result_for_black);

    qsort(result_for_black->moves, result_for_black->current_index, sizeof(ScoredMove), test_helper_compare_scored_move);
    qsort(expected_for_black, 2, sizeof(ScoredMove), test_helper_compare_scored_move);    

    TEST_ASSERT_EQUAL_INT(2, result_for_black->current_index);
    assert_move_lists_equal(expected_for_black, result_for_black->moves, 2);

    free_game(game_black);
    free(result_for_black);
}

void test_generate_all_white_pawns_capture_moves_from_position(void)
{
    char *position = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    ScoredMove expected[] = {
        CREATE_SCORED_MOVE(D5, E6, WHITE_PAWN, CAPTURE),
        CREATE_SCORED_MOVE(G2, H3, WHITE_PAWN, CAPTURE),
    };

    generate_all_white_pawns_capture_moves_from_game_state(game, result);

    qsort(result->moves, result->current_index, sizeof(ScoredMove), test_helper_compare_scored_move);
    qsort(expected, 2, sizeof(ScoredMove), test_helper_compare_scored_move);  
    
    TEST_ASSERT_EQUAL_INT(2, result->current_index);
    assert_move_lists_equal(expected, result->moves, 2);

    free_game(game);
    free(result);
}

void test_generate_all_black_pawns_capture_moves_from_position(void)
{
    char *position = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/Pp2P3/2N2Q1p/1PPBBPPP/R3K2R b KQkq a3 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    ScoredMove expected[] = {
        CREATE_SCORED_MOVE(B4, C3, BLACK_PAWN, CAPTURE),
        CREATE_SCORED_MOVE(B4, A3, BLACK_PAWN, EN_PASSANT_CAPTURE),
        CREATE_SCORED_MOVE(E6, D5, BLACK_PAWN, CAPTURE),
        CREATE_SCORED_MOVE(H3, G2, BLACK_PAWN, CAPTURE),
    };

    generate_all_black_pawns_capture_moves_from_game_state(game, result);

    qsort(result->moves, result->current_index, sizeof(ScoredMove), test_helper_compare_scored_move);
    qsort(expected, 4, sizeof(ScoredMove), test_helper_compare_scored_move);  
    
    TEST_ASSERT_EQUAL_INT(4, result->current_index);
    assert_move_lists_equal(expected, result->moves, 4);

    free_game(game);
    free(result);
}
// #endif // TEST