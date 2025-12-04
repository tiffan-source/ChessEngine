
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

void setUp(void)
{
    initialize_move_generation_databases();
}

void tearDown(void)
{
}

void test_min_max_sould_return_evaluation_at_depth_0(void)
{
    Game* game = create_game();

    ScoredMove evaluation = min_max_best_move_max(game, 0);

    // Each side has 8 pawns worth 100 each, so evaluation should be 0
    TEST_ASSERT_EQUAL_INT(0, evaluation.score);
}

void test_min_max_should_identify_checkmate_in_one_move(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/ppppp2p/8/5pp1/8/3PP3/PPP2PPP/RNBQK1BR w KQkq - 0 1");

    ScoredMove evaluation = min_max_best_move_max(game, 2);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - 1, evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D1, H5, WHITE_QUEEN, QUIET_MOVES), evaluation.move);
}

void test_min_max_should_identify_checkmate_in_two_move(void)
{
    Game* game = create_game_from_FEN("5k2/2PK1p2/pq6/6Q1/7P/4P3/8/8 b - - 0 1");

    ScoredMove evaluation = min_max_best_move_min(game, 4);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MIN + 1, evaluation.score);
    print_move(evaluation.move);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(B6, E6, BLACK_QUEEN, QUIET_MOVES), evaluation.move);
}

void test_negamax_should_identify_material_advantage_for_white(void)
{
    Game* game = create_game_from_FEN("8/6k1/1Kpp4/8/8/4PP2/8/8 w - - 0 1");


    ScoredMove evaluation = negamax_best_move(game, 1);

    // White should have a material advantage of +3
    TEST_ASSERT_EQUAL_INT(1, evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(B6, C6, WHITE_KING, CAPTURE), evaluation.move);
}

void test_negamax_should_identify_material_advantage_for_black(void)
{
    Game* game = create_game_from_FEN("7K/8/2pp4/8/8/4PPk1/8/8 b - - 0 1");


    ScoredMove evaluation = negamax_best_move(game, 1);

    // White should have a material advantage of +3
    TEST_ASSERT_EQUAL_INT(1, evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(G3, F3, BLACK_KING, CAPTURE), evaluation.move);
}

void test_negamax_should_identify_checkmate_in_one_move_for_white(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/ppppp2p/8/5pp1/8/3PP3/PPP2PPP/RNBQK1BR w KQkq - 0 1");

    ScoredMove evaluation = negamax_best_move(game, 2);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - 1, evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D1, H5, WHITE_QUEEN, QUIET_MOVES), evaluation.move);
}

void test_negamax_should_identify_checkmate_in_one_move_for_black(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/pppp1ppp/4p3/8/6P1/5P2/PPPPP2P/RNBQKBNR b KQkq - 0 1");

    ScoredMove evaluation = negamax_best_move(game, 2);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - 1, evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D8, H4, BLACK_QUEEN, QUIET_MOVES), evaluation.move);
}

void test_negamax_should_identify_checkmate_in_two_move_for_white(void)
{
    Game* game = create_game_from_FEN("r1bq2r1/b4pk1/p1pp1p2/1p2pP2/1P2P1PB/3P4/1PPQ2P1/R3K2R w");

    ScoredMove evaluation = negamax_best_move(game, 4);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - 1, evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D2, H6, WHITE_QUEEN, QUIET_MOVES), evaluation.move);
}

void test_negamax_should_identify_checkmate_in_two_move_for_black(void)
{
    Game* game = create_game_from_FEN("6k1/pp4p1/2p5/2bp4/8/P5Pb/1P3rrP/2BRRN1K b - - 0 1");

    ScoredMove evaluation = negamax_best_move(game, 4);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - 1, evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(G2, G1, BLACK_ROOK, QUIET_MOVES), evaluation.move);
}


// #endif // TEST
