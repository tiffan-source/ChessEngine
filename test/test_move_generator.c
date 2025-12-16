

#include "unity.h"

#include "move_generator.h"

#include "rooks_moves.h"
#include "knights_moves.h"
#include "bishops_moves.h"
#include "queens_moves.h"
#include "pawns_moves.h"
#include "king_moves.h"
#include "game.h"
#include "moves.h"
#include "board.h"
#include "binary_tools.h"
#include "pieces.h"

void setUp(void)
{
    initialize_move_generation_databases();
}

void tearDown(void)
{
}

void test_find_all_move_for_black_issue_1(void)
{
    char * fen = "kR6/8/8/8/7p/4BN1P/8/3K4 b - - 14 51";

    Game *game_black = create_game_from_FEN(fen);

    U64 result = generate_moves_from_position_at_depth(game_black, 1);

    TEST_ASSERT_EQUAL_UINT64(1, result);
}


void test_find_all_move_for_black_issue_2(void)
{
    char * fen = "R1r1k2r/8/8/8/8/8/8/4K2R b k - 4 3";

    Game *game_black = create_game_from_FEN(fen);

    U64 result = generate_moves_from_position_at_depth(game_black, 1);

    TEST_ASSERT_EQUAL_UINT64(18, result);
}
