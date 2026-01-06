
// #ifdef TEST

#include "unity.h"

#include "standard_lib.h"
#include "search_move.h"
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
#include "zobrist_key.h"
#include "tt.h"
#include "pv.h"

TranspositionTable* tt;

void setUp(void)
{
    initialize_magic_zobrist_numbers();
    initialize_move_generation_databases();
    tt = malloc(sizeof(TranspositionTable));
    initialize_transposition_table(tt);
    init_config(5);
}

void tearDown(void)
{
    free_config();
    free(tt);
}

void test_should_return_evaluation_at_depth_0(void)
{
    Game* game = create_game();

    set_depth(0);
    ScoredMove evaluation = nega_alpha_beta(game, 0, MIN, MAX, tt);

    TEST_ASSERT_EQUAL_INT(0, evaluation.score);
    free_game(game);
}

void test_should_identify_checkmate_in_one_move(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/ppppp2p/8/5pp1/8/3PP3/PPP2PPP/RNBQK1BR w KQkq - 0 1");

    set_depth(2);
    ScoredMove evaluation = nega_alpha_beta(game, 2, MIN, MAX, tt);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D1, H5, WHITE_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_two_move(void)
{
    Game* game = create_game_from_FEN("5k2/2PK1p2/pq6/6Q1/7P/4P3/8/8 b - - 0 1");

    set_depth(4);
    ScoredMove evaluation = nega_alpha_beta(game, 4, MIN, MAX, tt);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(B6, E6, BLACK_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_material_advantage_for_white(void)
{
    Game* game = create_game_from_FEN("8/6k1/1Kpp4/8/8/4PP2/8/8 w - - 0 1");

    set_depth(1);
    ScoredMove evaluation = nega_alpha_beta(game, 1, MIN, MAX, tt);

    // White should have a material advantage of +3
    TEST_ASSERT_TRUE(evaluation.score > 0);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(B6, C6, WHITE_KING, CAPTURE), evaluation.move);

    free_game(game);
}

void test_should_identify_material_advantage_for_black(void)
{
    Game* game = create_game_from_FEN("7K/8/2pp4/8/8/4PPk1/8/8 b - - 0 1");

    set_depth(1);
    ScoredMove evaluation = nega_alpha_beta(game, 1, MIN, MAX, tt);

    // White should have a material advantage of +3
    TEST_ASSERT_TRUE(evaluation.score > 0);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(G3, F3, BLACK_KING, CAPTURE), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_one_move_for_white(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/ppppp2p/8/5pp1/8/3PP3/PPP2PPP/RNBQK1BR w KQkq - 0 1");

    set_depth(2);
    ScoredMove evaluation = nega_alpha_beta(game, 2, MIN, MAX, tt);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D1, H5, WHITE_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_one_move_for_black(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/pppp1ppp/4p3/8/6P1/5P2/PPPPP2P/RNBQKBNR b KQkq - 0 1");

    set_depth(2);
    ScoredMove evaluation = nega_alpha_beta(game, 2, MIN, MAX, tt);

    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D8, H4, BLACK_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_two_move_for_white(void)
{
    Game* game = create_game_from_FEN("r1bq2r1/b4pk1/p1pp1p2/1p2pP2/1P2P1PB/3P4/1PPQ2P1/R3K2R w");

    set_depth(4);
    ScoredMove evaluation = nega_alpha_beta(game, 4, MIN, MAX, tt);

    // Checkmate should return a very high positive evaluation
    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(D2, H6, WHITE_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_two_move_for_black(void)
{
    Game* game = create_game_from_FEN("6k1/pp4p1/2p5/2bp4/8/P5Pb/1P3rrP/2BRRN1K b - - 0 1");

    set_depth(4);
    ScoredMove evaluation = nega_alpha_beta(game, 4, MIN, MAX, tt);

    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(G2, G1, BLACK_ROOK, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_three_move_for_black(void)
{
    Game* game = create_game_from_FEN("2r3k1/p4p2/3Rp2p/1p2P1pK/8/1P4P1/P3Q2P/1q6 b - - 0 1");

    set_depth(6);
    ScoredMove evaluation = nega_alpha_beta(game, 6, MIN, MAX, tt);

    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(B1, G6, BLACK_QUEEN, QUIET_MOVES), evaluation.move);

    free_game(game);
}

void test_should_identify_checkmate_in_three_move_for_white(void)
{
    Game* game = create_game_from_FEN("1k5r/pP3ppp/3p2b1/1BN1n3/1Q2P3/P1B5/KP3P1P/7q w - - 1 0");

    set_depth(6);
    ScoredMove evaluation = nega_alpha_beta(game, 6, MIN, MAX, tt);

    TEST_ASSERT_EQUAL_INT(MAX - (get_depth() - 1), evaluation.score);
    TEST_ASSERT_EQUAL_UINT(CREATE_MOVE(C5, A6, WHITE_KNIGHT, QUIET_MOVES), evaluation.move);

    free_game(game);
}

// #endif // TEST
