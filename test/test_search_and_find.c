
// #ifdef TEST

#include "unity.h"

#include "search_and_find.h"
#include "king_moves.h"
#include "game.h"
#include "board.h"
#include "moves.h"
#include "binary_tools.h"
#include "move_generator.h"
#include "evaluation.h"
#include "knights_moves.h"
#include "pawns_moves.h"
#include "rooks_moves.h"
#include "bishops_moves.h"
#include "queens_moves.h"
#include "pieces.h"
#include "config.h"
#include "move_ordering.h"

void setUp(void)
{
    initialize_move_generation_databases();
    init_config(5);
}

void tearDown(void)
{
    free_config();
}

void test_sould_return_evaluation_at_depth_0(void)
{
    Game* game = create_game();
    PV pv = { .move_count = 0 };

    set_depth(0);
    ScoredMove evaluation = nega_alpha_beta(game, 0, MIN, MAX, &pv);

    TEST_ASSERT_EQUAL_INT(0, evaluation.score);
    free_game(game);
}

void test_should_identify_checkmate_in_one_move(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/ppppp2p/8/5pp1/8/3PP3/PPP2PPP/RNBQK1BR w KQkq - 0 1");
    PV pv = { .move_count = 0 };

    set_depth(2);
    ScoredMove evaluation = nega_alpha_beta(game, 2, MIN, MAX, &pv);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D1, H5, WHITE_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_two_move(void)
{
    Game* game = create_game_from_FEN("5k2/2PK1p2/pq6/6Q1/7P/4P3/8/8 b - - 0 1");

    set_depth(4);
    PV pv = { .move_count = 0 };
    ScoredMove evaluation = nega_alpha_beta(game, 4, MIN, MAX, &pv);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(B6, E6, BLACK_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_material_advantage_for_white(void)
{
    Game* game = create_game_from_FEN("8/6k1/1Kpp4/8/8/4PP2/8/8 w - - 0 1");

    set_depth(1);
    PV pv = { .move_count = 0 };
    ScoredMove evaluation = nega_alpha_beta(game, 1, MIN, MAX, &pv);

    // White should have a material advantage of +3
    TEST_ASSERT_EQUAL_INT(1, evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(B6, C6, WHITE_KING, CAPTURE), evaluation.move);

    free_game(game);
}

void test_should_identify_material_advantage_for_black(void)
{
    Game* game = create_game_from_FEN("7K/8/2pp4/8/8/4PPk1/8/8 b - - 0 1");

    set_depth(1);
    PV pv = { .move_count = 0 };
    ScoredMove evaluation = nega_alpha_beta(game, 1, MIN, MAX, &pv);

    // White should have a material advantage of +3
    TEST_ASSERT_EQUAL_INT(1, evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(G3, F3, BLACK_KING, CAPTURE), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_one_move_for_white(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/ppppp2p/8/5pp1/8/3PP3/PPP2PPP/RNBQK1BR w KQkq - 0 1");

    set_depth(2);
    PV pv = { .move_count = 0 };
    ScoredMove evaluation = nega_alpha_beta(game, 2, MIN, MAX, &pv);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D1, H5, WHITE_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_one_move_for_black(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/pppp1ppp/4p3/8/6P1/5P2/PPPPP2P/RNBQKBNR b KQkq - 0 1");

    set_depth(2);
    PV pv = { .move_count = 0 };
    ScoredMove evaluation = nega_alpha_beta(game, 2, MIN, MAX, &pv);

    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D8, H4, BLACK_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_two_move_for_white(void)
{
    Game* game = create_game_from_FEN("r1bq2r1/b4pk1/p1pp1p2/1p2pP2/1P2P1PB/3P4/1PPQ2P1/R3K2R w");

    set_depth(4);
    PV pv = { .move_count = 0 };
    ScoredMove evaluation = nega_alpha_beta(game, 4, MIN, MAX, &pv);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D2, H6, WHITE_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_two_move_for_black(void)
{
    Game* game = create_game_from_FEN("6k1/pp4p1/2p5/2bp4/8/P5Pb/1P3rrP/2BRRN1K b - - 0 1");

    set_depth(4);
    PV pv = { .move_count = 0 };
    ScoredMove evaluation = nega_alpha_beta(game, 4, MIN, MAX, &pv);

    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() -1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(G2, G1, BLACK_ROOK, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_three_move_for_black(void)
{
    Game* game = create_game_from_FEN("2r3k1/p4p2/3Rp2p/1p2P1pK/8/1P4P1/P3Q2P/1q6 b - - 0 1");

    set_depth(6);
    PV pv = { .move_count = 0 };
    ScoredMove evaluation = nega_alpha_beta(game, 6, MIN, MAX, &pv);

    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(B1, G6, BLACK_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_three_move_for_white(void)
{
    Game* game = create_game_from_FEN("1k5r/pP3ppp/3p2b1/1BN1n3/1Q2P3/P1B5/KP3P1P/7q w - - 1 0");

    set_depth(6);
    PV pv = { .move_count = 0 };
    ScoredMove evaluation = nega_alpha_beta(game, 6, MIN, MAX, &pv);

    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(C5, A6, WHITE_KNIGHT, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_nega_alpha_beta_with_pv_should_get_the_best_move_list_at_depth_1(void)
{
    PV pv = { .move_count = 0 };
    char *fen = "8/3k4/8/8/8/6r1/2K2P2/8 w - - 0 1";

    Move expected_moves[] = {
        CREATE_MOVE(F2, G3, WHITE_PAWN, CAPTURE),
    };

    Game* game = create_game_from_FEN(fen);

    set_depth(1);

    nega_alpha_beta(game, 1, MIN, MAX, &pv);
    
    TEST_ASSERT_EQUAL_INT(1, pv.move_count);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_moves, pv.moves, pv.move_count);
    
    free_game(game);
}

void test_nega_alpha_beta_with_pv_should_get_the_best_move_list_at_depth_2(void)
{
    PV pv = { .move_count = 0 };
    char *fen = "8/2R3qk/8/8/8/8/2K5/8 w - - 0 1";

    Move expected_moves[] = {
        CREATE_MOVE(C7, G7, WHITE_ROOK, CAPTURE),
        CREATE_MOVE(H7, G7, BLACK_KING, CAPTURE),
    };

    Game* game = create_game_from_FEN(fen);

    set_depth(2);

    nega_alpha_beta(game, 2, MIN, MAX, &pv);

    TEST_ASSERT_EQUAL_INT(2, pv.move_count);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_moves, pv.moves, pv.move_count);
    
    free_game(game);
}

void test_nega_alpha_beta_with_pv_should_get_the_best_move_list_at_depth_6(void)
{
    PV pv = { .move_count = 0 };
    char *fen = "2r3k1/p4p2/3Rp2p/1p2P1pK/8/1P4P1/P3Q2P/1q6 b - - 0 1";

    Move expected_moves[] = {
        CREATE_MOVE(B1, G6, BLACK_QUEEN, QUIET_MOVES),
        CREATE_MOVE(H5, G4, WHITE_KING, QUIET_MOVES),
        CREATE_MOVE(G6, F5, BLACK_QUEEN, QUIET_MOVES),
        CREATE_MOVE(G4, H5, WHITE_KING, QUIET_MOVES),
        CREATE_MOVE(F5, H3, BLACK_QUEEN, QUIET_MOVES),
    };

    Game* game = create_game_from_FEN(fen);

    set_depth(6);

    nega_alpha_beta(game, 6, MIN, MAX, &pv);

    TEST_ASSERT_EQUAL_INT(6, pv.move_count);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_moves, pv.moves, 5);
    
    free_game(game);
}



// #endif // TEST
