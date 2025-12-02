
#ifdef TEST

#include "unity.h"

#include "game.h"
#include "board.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_game_should_create_a_non_null_game(void)
{
    Game* game = create_game();
    TEST_ASSERT_NOT_NULL(game);

    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_black_pawn(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0xFF00ULL, game->black_pawns);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_white_pawn(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0xFF000000000000ULL, game->white_pawns);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_black_knight(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0x42ULL, game->black_knights);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_white_knight(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0x4200000000000000ULL, game->white_knights);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_black_bishops(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0x24ULL, game->black_bishops);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_white_bishops(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0x2400000000000000ULL, game->white_bishops);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_black_rooks(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0x81ULL, game->black_rooks);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_white_rooks(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0x8100000000000000ULL, game->white_rooks);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_black_queens(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0x8ULL, game->black_queens);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_white_queens(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0x800000000000000ULL, game->white_queens);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_black_king(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0x10ULL, game->black_king);
    
    free(game);
}

void test_game_should_create_new_game_with_valid_position_of_white_king(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_UINT64(0x1000000000000000ULL, game->white_king);
    
    free(game);
}

void test_game_should_create_new_game_with_turn_for_white(void)
{
    Game* game = create_game();

    TEST_ASSERT_EQUAL_INT(WHITE_TURN, game->turn);
    
    free(game);
}

void test_game_should_create_game_from_FEN_init_game_from_string_testing_piece_placement(void)
{
    char* FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Game* game = create_game_from_FEN(FEN);

    TEST_ASSERT_NOT_NULL(game);
    
    TEST_ASSERT_EQUAL_UINT64(0xFF00ULL, game->black_pawns);
    TEST_ASSERT_EQUAL_UINT64(0xFF000000000000ULL, game->white_pawns);

    TEST_ASSERT_EQUAL_UINT64(0x42ULL, game->black_knights);
    TEST_ASSERT_EQUAL_UINT64(0x4200000000000000ULL, game->white_knights);

    TEST_ASSERT_EQUAL_UINT64(0x24ULL, game->black_bishops);
    TEST_ASSERT_EQUAL_UINT64(0x2400000000000000ULL, game->white_bishops);

    TEST_ASSERT_EQUAL_UINT64(0x81ULL, game->black_rooks);
    TEST_ASSERT_EQUAL_UINT64(0x8100000000000000ULL, game->white_rooks);

    TEST_ASSERT_EQUAL_UINT64(0x8ULL, game->black_queens);
    TEST_ASSERT_EQUAL_UINT64(0x800000000000000ULL, game->white_queens);

    TEST_ASSERT_EQUAL_UINT64(0x10ULL, game->black_king);
    TEST_ASSERT_EQUAL_UINT64(0x1000000000000000ULL, game->white_king);

    free_game(game);
}

void test_game_should_create_game_from_FEN_tricky_position_game_from_string_testing_piece_placement(void)
{
    char* FEN = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
    Game* game = create_game_from_FEN(FEN);

    TEST_ASSERT_NOT_NULL(game);

    Bitboard expected_black_pawns = 0;
    expected_black_pawns = SET_BIT_ON_BITBOARD(expected_black_pawns, A6);
    expected_black_pawns = SET_BIT_ON_BITBOARD(expected_black_pawns, B7);
    expected_black_pawns = SET_BIT_ON_BITBOARD(expected_black_pawns, C7);
    expected_black_pawns = SET_BIT_ON_BITBOARD(expected_black_pawns, D6);
    expected_black_pawns = SET_BIT_ON_BITBOARD(expected_black_pawns, E5);
    expected_black_pawns = SET_BIT_ON_BITBOARD(expected_black_pawns, F7);
    expected_black_pawns = SET_BIT_ON_BITBOARD(expected_black_pawns, G7);
    expected_black_pawns = SET_BIT_ON_BITBOARD(expected_black_pawns, H7);
    TEST_ASSERT_EQUAL_UINT64(expected_black_pawns, game->black_pawns);

    Bitboard expected_white_pawns = 0;
    expected_white_pawns = SET_BIT_ON_BITBOARD(expected_white_pawns, A3);
    expected_white_pawns = SET_BIT_ON_BITBOARD(expected_white_pawns, B2);
    expected_white_pawns = SET_BIT_ON_BITBOARD(expected_white_pawns, C2);
    expected_white_pawns = SET_BIT_ON_BITBOARD(expected_white_pawns, D3);
    expected_white_pawns = SET_BIT_ON_BITBOARD(expected_white_pawns, E4);
    expected_white_pawns = SET_BIT_ON_BITBOARD(expected_white_pawns, F2);
    expected_white_pawns = SET_BIT_ON_BITBOARD(expected_white_pawns, G2);
    expected_white_pawns = SET_BIT_ON_BITBOARD(expected_white_pawns, H2);
    TEST_ASSERT_EQUAL_UINT64(expected_white_pawns, game->white_pawns);

    Bitboard expected_black_knights = 0;
    expected_black_knights = SET_BIT_ON_BITBOARD(expected_black_knights, C6);
    expected_black_knights = SET_BIT_ON_BITBOARD(expected_black_knights, F6);
    TEST_ASSERT_EQUAL_UINT64(expected_black_knights, game->black_knights);

    Bitboard expected_white_knights = 0;
    expected_white_knights = SET_BIT_ON_BITBOARD(expected_white_knights, C3);
    expected_white_knights = SET_BIT_ON_BITBOARD(expected_white_knights, F3);
    TEST_ASSERT_EQUAL_UINT64(expected_white_knights, game->white_knights);

    Bitboard expected_black_bishops = 0;
    expected_black_bishops = SET_BIT_ON_BITBOARD(expected_black_bishops, C5);
    expected_black_bishops = SET_BIT_ON_BITBOARD(expected_black_bishops, G4);
    TEST_ASSERT_EQUAL_UINT64(expected_black_bishops, game->black_bishops);

    Bitboard expected_white_bishops = 0;
    expected_white_bishops = SET_BIT_ON_BITBOARD(expected_white_bishops, C4);
    expected_white_bishops = SET_BIT_ON_BITBOARD(expected_white_bishops, G5);
    TEST_ASSERT_EQUAL_UINT64(expected_white_bishops, game->white_bishops);

    Bitboard expected_black_rooks = 0;
    expected_black_rooks = SET_BIT_ON_BITBOARD(expected_black_rooks, A8);
    expected_black_rooks = SET_BIT_ON_BITBOARD(expected_black_rooks, F8);
    TEST_ASSERT_EQUAL_UINT64(expected_black_rooks, game->black_rooks);

    Bitboard expected_white_rooks = 0;
    expected_white_rooks = SET_BIT_ON_BITBOARD(expected_white_rooks, A1);
    expected_white_rooks = SET_BIT_ON_BITBOARD(expected_white_rooks, F1);
    TEST_ASSERT_EQUAL_UINT64(expected_white_rooks, game->white_rooks);

    Bitboard expected_black_queens = 0;
    expected_black_queens = SET_BIT_ON_BITBOARD(expected_black_queens, E7);
    TEST_ASSERT_EQUAL_UINT64(expected_black_queens, game->black_queens);

    Bitboard expected_white_queens = 0;
    expected_white_queens = SET_BIT_ON_BITBOARD(expected_white_queens, E2);
    TEST_ASSERT_EQUAL_UINT64(expected_white_queens, game->white_queens);

    Bitboard expected_black_king = 0;
    expected_black_king = SET_BIT_ON_BITBOARD(expected_black_king, G8);
    TEST_ASSERT_EQUAL_UINT64(expected_black_king, game->black_king);

    Bitboard expected_white_king = 0;
    expected_white_king = SET_BIT_ON_BITBOARD(expected_white_king, G1);
    TEST_ASSERT_EQUAL_UINT64(expected_white_king, game->white_king);

    free_game(game);
}

void test_game_should_create_game_from_FEN_with_black_to_move(void)
{
    char* FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
    Game* game = create_game_from_FEN(FEN);

    TEST_ASSERT_NOT_NULL(game);
    
    TEST_ASSERT_EQUAL_INT(BLACK_TURN, game->turn);

    free_game(game);
}


void test_game_should_create_game_from_FEN_with_white_to_move(void)
{
    char* FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Game* game = create_game_from_FEN(FEN);

    TEST_ASSERT_NOT_NULL(game);
    
    TEST_ASSERT_EQUAL_INT(WHITE_TURN, game->turn);

    free_game(game);
}

void test_game_should_create_game_from_FEN_and_set_castling_rights(void)
{
    char* FEN1 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Game* game1 = create_game_from_FEN(FEN1);

    char* FEN2 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";
    Game* game2 = create_game_from_FEN(FEN2);

    char* FEN3 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Kkq - 0 1";
    Game* game3 = create_game_from_FEN(FEN3);

    char* FEN4 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQq - 0 1";
    Game* game4 = create_game_from_FEN(FEN4);

    char* FEN5 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Qkq - 0 1";
    Game* game5 = create_game_from_FEN(FEN5);
    
    
    TEST_ASSERT_EQUAL_INT(15, game1->castling_rights);
    TEST_ASSERT_EQUAL_INT(0, game2->castling_rights);
    TEST_ASSERT_EQUAL_INT(11, game3->castling_rights);
    TEST_ASSERT_EQUAL_INT(13, game4->castling_rights);
    TEST_ASSERT_EQUAL_INT(7, game5->castling_rights);

    free_game(game1);
    free_game(game2);
    free_game(game3);
    free_game(game4);
    free_game(game5);
}

void test_game_should_create_game_from_FEN_with_en_passant_target_square(void)
{
    char* FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - f3 0 1";
    Game* game = create_game_from_FEN(FEN);

    TEST_ASSERT_NOT_NULL(game);
    
    TEST_ASSERT_EQUAL_INT(F3, game->en_passant_target_square); 

    free_game(game);
}

void test_game_should_create_game_from_FEN_with_no_en_passant_target_square(void)
{
    char* FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";
    Game* game = create_game_from_FEN(FEN);

    TEST_ASSERT_NOT_NULL(game);
    
    TEST_ASSERT_EQUAL_INT(-1, game->en_passant_target_square); 

    free_game(game);
}

#endif // TEST
