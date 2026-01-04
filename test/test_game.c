

#include "unity.h"

#include "game.h"
#include "board.h"
#include "binary_tools.h"
#include "zobrist_key.h"

void setUp(void)
{
    initialize_magic_zobrist_numbers();
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


void test_transposition_should_return_valid_zobrist_key_for_two_king_on_e1_and_e8_white_turn_and_no_castling_rights(void)
{
    Game* game = create_game_from_FEN("4k3/8/8/8/8/8/8/4K3 w - - 0 1");

    U64 zobrist_key = create_zobrist_key_from_game_state(game);

    U64 expected_key = 0;
    expected_key ^= king_zobrist_magic_number[1][E1];   // White king on e1
    expected_key ^= king_zobrist_magic_number[0][E8];  // Black king on e8
    expected_key ^= castling_rights_zobrist_magic_number[0]; // No castling rights

    TEST_ASSERT_EQUAL_UINT64(expected_key, zobrist_key);
}

void test_transposition_should_return_valid_zobrist_key_for_starting_position(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    U64 zobrist_key = create_zobrist_key_from_game_state(game);

    U64 expected_key = 0;
    // White Pieces
    expected_key ^= rook_zobrist_magic_number[1][A1];
    expected_key ^= knight_zobrist_magic_number[1][B1];
    expected_key ^= bishop_zobrist_magic_number[1][C1];
    expected_key ^= queen_zobrist_magic_number[1][D1];
    expected_key ^= king_zobrist_magic_number[1][E1];
    expected_key ^= bishop_zobrist_magic_number[1][F1];
    expected_key ^= knight_zobrist_magic_number[1][G1];
    expected_key ^= rook_zobrist_magic_number[1][H1];
    for (int i = A2; i <= H2; i++) expected_key ^= pawn_zobrist_magic_number[1][i];

    // Black Pieces
    expected_key ^= rook_zobrist_magic_number[0][A8];
    expected_key ^= knight_zobrist_magic_number[0][B8];
    expected_key ^= bishop_zobrist_magic_number[0][C8];
    expected_key ^= queen_zobrist_magic_number[0][D8];
    expected_key ^= king_zobrist_magic_number[0][E8];
    expected_key ^= bishop_zobrist_magic_number[0][F8];
    expected_key ^= knight_zobrist_magic_number[0][G8];
    expected_key ^= rook_zobrist_magic_number[0][H8];
    for (int i = A7; i <= H7; i++) expected_key ^= pawn_zobrist_magic_number[0][i];

    // Castling Rights (KQkq = 15)
    expected_key ^= castling_rights_zobrist_magic_number[15];

    TEST_ASSERT_EQUAL_UINT64(expected_key, zobrist_key);
}

void test_transposition_should_include_black_to_move(void)
{
    Game* game = create_game_from_FEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");

    U64 zobrist_key = create_zobrist_key_from_game_state(game);

    U64 expected_key = 0;
    // White Pieces (Pawn on E4 instead of E2)
    expected_key ^= rook_zobrist_magic_number[1][A1];
    expected_key ^= knight_zobrist_magic_number[1][B1];
    expected_key ^= bishop_zobrist_magic_number[1][C1];
    expected_key ^= queen_zobrist_magic_number[1][D1];
    expected_key ^= king_zobrist_magic_number[1][E1];
    expected_key ^= bishop_zobrist_magic_number[1][F1];
    expected_key ^= knight_zobrist_magic_number[1][G1];
    expected_key ^= rook_zobrist_magic_number[1][H1];
    for (int i = A2; i <= H2; i++) {
        if (i != E2) expected_key ^= pawn_zobrist_magic_number[1][i];
    }
    expected_key ^= pawn_zobrist_magic_number[1][E4];

    // Black Pieces
    expected_key ^= rook_zobrist_magic_number[0][A8];
    expected_key ^= knight_zobrist_magic_number[0][B8];
    expected_key ^= bishop_zobrist_magic_number[0][C8];
    expected_key ^= queen_zobrist_magic_number[0][D8];
    expected_key ^= king_zobrist_magic_number[0][E8];
    expected_key ^= bishop_zobrist_magic_number[0][F8];
    expected_key ^= knight_zobrist_magic_number[0][G8];
    expected_key ^= rook_zobrist_magic_number[0][H8];
    for (int i = A7; i <= H7; i++) expected_key ^= pawn_zobrist_magic_number[0][i];

    // Black to move
    expected_key ^= black_to_move_zobrist_magic_number;

    // Castling Rights (KQkq = 15)
    expected_key ^= castling_rights_zobrist_magic_number[15];

    // En Passant (e3)
    expected_key ^= en_passant_square_zobrist_magic_number[E3];

    TEST_ASSERT_EQUAL_UINT64(expected_key, zobrist_key);
}

void test_transposition_should_handle_castling_rights_changes(void)
{
    // White King Side (K) and Black Queen Side (q) -> 8 + 1 = 9
    Game* game = create_game_from_FEN("r3k2r/8/8/8/8/8/8/R3K2R w Kq - 0 1");

    U64 zobrist_key = create_zobrist_key_from_game_state(game);

    U64 expected_key = 0;
    expected_key ^= rook_zobrist_magic_number[1][A1];
    expected_key ^= king_zobrist_magic_number[1][E1];
    expected_key ^= rook_zobrist_magic_number[1][H1];
    
    expected_key ^= rook_zobrist_magic_number[0][A8];
    expected_key ^= king_zobrist_magic_number[0][E8];
    expected_key ^= rook_zobrist_magic_number[0][H8];

    expected_key ^= castling_rights_zobrist_magic_number[9];

    TEST_ASSERT_EQUAL_UINT64(expected_key, zobrist_key);
}

void test_transposition_should_handle_mixed_castling_rights_Qk(void)
{
    // White Queen Side (Q) and Black King Side (k) -> 4 + 2 = 6
    Game* game = create_game_from_FEN("r3k2r/8/8/8/8/8/8/R3K2R w Qk - 0 1");

    U64 zobrist_key = create_zobrist_key_from_game_state(game);

    U64 expected_key = 0;
    expected_key ^= rook_zobrist_magic_number[1][A1];
    expected_key ^= king_zobrist_magic_number[1][E1];
    expected_key ^= rook_zobrist_magic_number[1][H1];
    
    expected_key ^= rook_zobrist_magic_number[0][A8];
    expected_key ^= king_zobrist_magic_number[0][E8];
    expected_key ^= rook_zobrist_magic_number[0][H8];

    expected_key ^= castling_rights_zobrist_magic_number[6];

    TEST_ASSERT_EQUAL_UINT64(expected_key, zobrist_key);
}

void test_transposition_should_handle_en_passant_target_a3(void)
{
    // 1. a4 (White plays a4, en passant target a3)
    Game* game = create_game_from_FEN("rnbqkbnr/pppppppp/8/8/P7/8/1PPPPPPP/RNBQKBNR b KQkq a3 0 1");

    U64 zobrist_key = create_zobrist_key_from_game_state(game);

    U64 expected_key = 0;
    
    // White Pieces (Pawn on A4 instead of A2)
    expected_key ^= rook_zobrist_magic_number[1][A1];
    expected_key ^= knight_zobrist_magic_number[1][B1];
    expected_key ^= bishop_zobrist_magic_number[1][C1];
    expected_key ^= queen_zobrist_magic_number[1][D1];
    expected_key ^= king_zobrist_magic_number[1][E1];
    expected_key ^= bishop_zobrist_magic_number[1][F1];
    expected_key ^= knight_zobrist_magic_number[1][G1];
    expected_key ^= rook_zobrist_magic_number[1][H1];
    
    expected_key ^= pawn_zobrist_magic_number[1][A4];
    for (int i = B2; i <= H2; i++) expected_key ^= pawn_zobrist_magic_number[1][i];

    // Black Pieces (Standard)
    expected_key ^= rook_zobrist_magic_number[0][A8];
    expected_key ^= knight_zobrist_magic_number[0][B8];
    expected_key ^= bishop_zobrist_magic_number[0][C8];
    expected_key ^= queen_zobrist_magic_number[0][D8];
    expected_key ^= king_zobrist_magic_number[0][E8];
    expected_key ^= bishop_zobrist_magic_number[0][F8];
    expected_key ^= knight_zobrist_magic_number[0][G8];
    expected_key ^= rook_zobrist_magic_number[0][H8];
    for (int i = A7; i <= H7; i++) expected_key ^= pawn_zobrist_magic_number[0][i];

    // Black to move
    expected_key ^= black_to_move_zobrist_magic_number;

    // Castling Rights (KQkq = 15)
    expected_key ^= castling_rights_zobrist_magic_number[15];

    // En Passant (a3)
    expected_key ^= en_passant_square_zobrist_magic_number[A3];

    TEST_ASSERT_EQUAL_UINT64(expected_key, zobrist_key);
}

void test_transposition_should_handle_complex_sicilian_position(void)
{
    // Sicilian Dragon: "r1bq1rk1/pp2ppbp/2np1np1/8/3NP3/2N1BP2/PPPQ2PP/R3KB1R w KQ - 3 9"
    Game* game = create_game_from_FEN("r1bq1rk1/pp2ppbp/2np1np1/8/3NP3/2N1BP2/PPPQ2PP/R3KB1R w KQ - 3 9");

    U64 zobrist_key = create_zobrist_key_from_game_state(game);

    U64 expected_key = 0;

    // White Pieces
    // Rooks: A1, H1
    expected_key ^= rook_zobrist_magic_number[1][A1];
    expected_key ^= rook_zobrist_magic_number[1][H1];
    // Knights: C3, D4
    expected_key ^= knight_zobrist_magic_number[1][C3];
    expected_key ^= knight_zobrist_magic_number[1][D4];
    // Bishops: E3, F1
    expected_key ^= bishop_zobrist_magic_number[1][E3];
    expected_key ^= bishop_zobrist_magic_number[1][F1];
    // Queen: D2
    expected_key ^= queen_zobrist_magic_number[1][D2];
    // King: E1
    expected_key ^= king_zobrist_magic_number[1][E1];
    // Pawns: A2, B2, C2, E4, F3, G2, H2
    expected_key ^= pawn_zobrist_magic_number[1][A2];
    expected_key ^= pawn_zobrist_magic_number[1][B2];
    expected_key ^= pawn_zobrist_magic_number[1][C2];
    expected_key ^= pawn_zobrist_magic_number[1][E4];
    expected_key ^= pawn_zobrist_magic_number[1][F3];
    expected_key ^= pawn_zobrist_magic_number[1][G2];
    expected_key ^= pawn_zobrist_magic_number[1][H2];

    // Black Pieces
    // Rooks: A8, F8
    expected_key ^= rook_zobrist_magic_number[0][A8];
    expected_key ^= rook_zobrist_magic_number[0][F8];
    // Knights: C6, F6
    expected_key ^= knight_zobrist_magic_number[0][C6];
    expected_key ^= knight_zobrist_magic_number[0][F6];
    // Bishops: C8, G7
    expected_key ^= bishop_zobrist_magic_number[0][C8];
    expected_key ^= bishop_zobrist_magic_number[0][G7];
    // Queen: D8
    expected_key ^= queen_zobrist_magic_number[0][D8];
    // King: G8
    expected_key ^= king_zobrist_magic_number[0][G8];
    // Pawns: A7, B7, D6, E7, F7, G6, H7
    expected_key ^= pawn_zobrist_magic_number[0][A7];
    expected_key ^= pawn_zobrist_magic_number[0][B7];
    expected_key ^= pawn_zobrist_magic_number[0][D6];
    expected_key ^= pawn_zobrist_magic_number[0][E7];
    expected_key ^= pawn_zobrist_magic_number[0][F7];
    expected_key ^= pawn_zobrist_magic_number[0][G6];
    expected_key ^= pawn_zobrist_magic_number[0][H7];

    // White to move (no extra key)

    // Castling Rights: KQ (8 + 4 = 12)
    expected_key ^= castling_rights_zobrist_magic_number[12];

    // En Passant: None (-1)

    TEST_ASSERT_EQUAL_UINT64(expected_key, zobrist_key);
}
