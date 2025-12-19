

#include "unity.h"
#include "evaluation.h"
#include "game.h"
#include "board.h"
#include "binary_tools.h"
#include "king_moves.h"
#include "moves.h"
#include "rooks_moves.h"
#include "bishops_moves.h"
#include "pawns_moves.h"
#include "knights_moves.h"
#include "king_moves.h"
#include "pieces.h"
#include "move_generator.h"
#include "queens_moves.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_evaluation_material_should_return_0_for_equal_game(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL(0, material_evaluation_for_side(game));

    free_game(game);
}

void test_evaluation_material_should_return_1_for_on_pawn_advantage_for_white(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/1ppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    TEST_ASSERT_EQUAL(100, material_evaluation_for_side(game));

    free_game(game);
}

void test_evaluation_material_should_return_minus_1_for_on_pawn_advantage_for_black(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/1PPPPPPP/RNBQKBNR w KQkq - 0 1");

    TEST_ASSERT_EQUAL(-100, material_evaluation_for_side(game));

    free_game(game);
}


void test_evaluation_material_should_return_6_for_on_knight_advantage_for_white(void)
{
    Game* game = create_game_from_FEN("r1bqkb1r/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    TEST_ASSERT_EQUAL(600, material_evaluation_for_side(game));

    free_game(game);
}

void test_evaluation_material_should_return_minus_3_for_on_knight_advantage_for_black(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R1BQKBNR w KQkq - 0 1");

    TEST_ASSERT_EQUAL(-300, material_evaluation_for_side(game));

    free_game(game);
}


void test_evaluation_material_should_return_3_for_on_bishop_advantage_for_white(void)
{
    Game* game = create_game_from_FEN("rnbqk1nr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    TEST_ASSERT_EQUAL(350, material_evaluation_for_side(game));
    free_game(game);
}

void test_evaluation_material_should_return_minus_6_for_on_bishop_advantage_for_black(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RN1QK1NR w KQkq - 0 1");

    TEST_ASSERT_EQUAL(-700, material_evaluation_for_side(game));
    free_game(game);
}

void test_evaluation_material_should_return_4_for_on_rook_advantage_for_white(void)
{
    // Position : Blanc a une Tour de plus que Noir (FEN standard sans une Tour noire)
    // r1bqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
    // (Une Tour noire a été enlevée)
    Game* game = create_game_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/1NBQKBNR w KQkq - 0 1"); 

    // Avantage Noir : 0 - 400 = -400 
    TEST_ASSERT_EQUAL(-400, material_evaluation_for_side(game));

    free_game(game);
}

void test_evaluation_material_should_return_minus_9_for_on_queen_advantage_for_black(void)
{
    // Position : Noir a une Dame de plus que Blanc (FEN standard sans une Dame blanche)
    Game* game = create_game_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNB1KBNR w KQkq - 0 1"); 

    // Avantage Noir : 0 - 9 = -9
    TEST_ASSERT_EQUAL(-900, material_evaluation_for_side(game));
    
    free_game(game);
}

void test_evaluation_material_should_return_0_for_rook_for_knight_and_pawn(void)
{
    Game* game = create_game_from_FEN("rnbqkbn1/pppppppp/8/8/8/8/P1PPPPPP/R1BQKBNR w KQkq - 0 1"); 

    TEST_ASSERT_EQUAL(0, material_evaluation_for_side(game));

    free_game(game);
}

void test_evaluation_material_should_return_1_for_queen_for_two_rooks(void)
{
    Game* game = create_game_from_FEN("rnb1kbnr/pppppppp/8/8/8/8/PPPPPPPP/1NBQKBN1 w KQkq - 0 1"); 
    
    TEST_ASSERT_EQUAL(100, material_evaluation_for_side(game));

    free_game(game);
}