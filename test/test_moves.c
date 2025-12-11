
// #ifdef TEST

#include "unity.h"
#include "moves.h"
#include "pieces.h"
#include "board.h"
#include "binary_tools.h"

void setUp(void)
{
}

void tearDown(void)
{
}

// Using macros from moves.h for component extraction

// Test basic move creation with minimum values
void test_CREATE_MOVE_should_handle_minimum_values(void)
{
    Move move = CREATE_MOVE(A8, A8, BLACK_PAWN, QUIET_MOVES);
    
    TEST_ASSERT_EQUAL(A8, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(A8, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(BLACK_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(QUIET_MOVES, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test basic move creation with maximum values
void test_CREATE_MOVE_should_handle_maximum_values(void)
{
    Move move = CREATE_MOVE(H1, H1, WHITE_KING, QUEEN_PROMOTION_CAPTURE);
    
    TEST_ASSERT_EQUAL(H1, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(H1, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_KING, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(QUEEN_PROMOTION_CAPTURE, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test quiet pawn move
void test_CREATE_MOVE_should_handle_quiet_pawn_move(void)
{
    Move move = CREATE_MOVE(E2, E3, WHITE_PAWN, QUIET_MOVES);
    
    TEST_ASSERT_EQUAL(E2, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(E3, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(QUIET_MOVES, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test double pawn push
void test_CREATE_MOVE_should_handle_double_pawn_push(void)
{
    Move move = CREATE_MOVE(E2, E4, WHITE_PAWN, DOUBLE_PAWN_PUSH);
    
    TEST_ASSERT_EQUAL(E2, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(E4, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(DOUBLE_PAWN_PUSH, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test king side castling
void test_CREATE_MOVE_should_handle_king_castle(void)
{
    Move move = CREATE_MOVE(E1, G1, WHITE_KING, KING_CASTLE);
    
    TEST_ASSERT_EQUAL(E1, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(G1, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_KING, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(KING_CASTLE, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test queen side castling
void test_CREATE_MOVE_should_handle_queen_castle(void)
{
    Move move = CREATE_MOVE(E1, C1, WHITE_KING, QUEEN_CASTLE);
    
    TEST_ASSERT_EQUAL(E1, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(C1, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_KING, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(QUEEN_CASTLE, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test basic capture
void test_CREATE_MOVE_should_handle_capture(void)
{
    Move move = CREATE_MOVE(D4, E5, WHITE_KNIGHT, CAPTURE);
    
    TEST_ASSERT_EQUAL(D4, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(E5, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_KNIGHT, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test en passant capture
void test_CREATE_MOVE_should_handle_en_passant_capture(void)
{
    Move move = CREATE_MOVE(E5, D6, WHITE_PAWN, EN_PASSANT_CAPTURE);
    
    TEST_ASSERT_EQUAL(E5, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(D6, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(EN_PASSANT_CAPTURE, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test knight promotion
void test_CREATE_MOVE_should_handle_knight_promotion(void)
{
    Move move = CREATE_MOVE(E7, E8, WHITE_PAWN, KNIGHT_PROMOTION);
    
    TEST_ASSERT_EQUAL(E7, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(E8, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(KNIGHT_PROMOTION, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test bishop promotion
void test_CREATE_MOVE_should_handle_bishop_promotion(void)
{
    Move move = CREATE_MOVE(E7, E8, WHITE_PAWN, BISHOP_PROMOTION);
    
    TEST_ASSERT_EQUAL(E7, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(E8, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(BISHOP_PROMOTION, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test rook promotion
void test_CREATE_MOVE_should_handle_rook_promotion(void)
{
    Move move = CREATE_MOVE(E7, E8, WHITE_PAWN, ROOK_PROMOTION);
    
    TEST_ASSERT_EQUAL(E7, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(E8, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(ROOK_PROMOTION, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test queen promotion
void test_CREATE_MOVE_should_handle_queen_promotion(void)
{
    Move move = CREATE_MOVE(E7, E8, WHITE_PAWN, QUEEN_PROMOTION);
    
    TEST_ASSERT_EQUAL(E7, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(E8, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(QUEEN_PROMOTION, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test knight promotion with capture
void test_CREATE_MOVE_should_handle_knight_promotion_capture(void)
{
    Move move = CREATE_MOVE(E7, F8, WHITE_PAWN, KNIGHT_PROMOTION_CAPTURE);
    
    TEST_ASSERT_EQUAL(E7, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(F8, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(KNIGHT_PROMOTION_CAPTURE, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test bishop promotion with capture
void test_CREATE_MOVE_should_handle_bishop_promotion_capture(void)
{
    Move move = CREATE_MOVE(E7, F8, WHITE_PAWN, BISHOP_PROMOTION_CAPTURE);
    
    TEST_ASSERT_EQUAL(E7, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(F8, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(BISHOP_PROMOTION_CAPTURE, GET_MOVE_TYPE_FROM_MOVE (move));
}

// Test rook promotion with capture
void test_CREATE_MOVE_should_handle_rook_promotion_capture(void)
{
    Move move = CREATE_MOVE(E7, F8, WHITE_PAWN, ROOK_PROMOTION_CAPTURE);
    
    TEST_ASSERT_EQUAL(E7, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(F8, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(ROOK_PROMOTION_CAPTURE, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test queen promotion with capture
void test_CREATE_MOVE_should_handle_queen_promotion_capture(void)
{
    Move move = CREATE_MOVE(E7, F8, WHITE_PAWN, QUEEN_PROMOTION_CAPTURE);
    
    TEST_ASSERT_EQUAL(E7, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(F8, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(QUEEN_PROMOTION_CAPTURE, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test all piece types with basic moves
void test_CREATE_MOVE_should_handle_all_black_pieces(void)
{
    Move move1 = CREATE_MOVE(A7, A6, BLACK_PAWN, QUIET_MOVES);
    Move move2 = CREATE_MOVE(B8, C6, BLACK_KNIGHT, QUIET_MOVES);
    Move move3 = CREATE_MOVE(C8, D7, BLACK_BISHOP, QUIET_MOVES);
    Move move4 = CREATE_MOVE(A8, A7, BLACK_ROOK, QUIET_MOVES);
    Move move5 = CREATE_MOVE(D8, D7, BLACK_QUEEN, QUIET_MOVES);
    Move move6 = CREATE_MOVE(E8, F8, BLACK_KING, QUIET_MOVES);
    
    TEST_ASSERT_EQUAL(BLACK_PAWN, GET_PIECE_TYPE_FROM_MOVE(move1));
    TEST_ASSERT_EQUAL(BLACK_KNIGHT, GET_PIECE_TYPE_FROM_MOVE(move2));
    TEST_ASSERT_EQUAL(BLACK_BISHOP, GET_PIECE_TYPE_FROM_MOVE(move3));
    TEST_ASSERT_EQUAL(BLACK_ROOK, GET_PIECE_TYPE_FROM_MOVE(move4));
    TEST_ASSERT_EQUAL(BLACK_QUEEN, GET_PIECE_TYPE_FROM_MOVE(move5));
    TEST_ASSERT_EQUAL(BLACK_KING, GET_PIECE_TYPE_FROM_MOVE(move6));
}

// Test boundary squares
void test_CREATE_MOVE_should_handle_boundary_squares(void)
{
    Move move1 = CREATE_MOVE(A8, H8, WHITE_QUEEN, QUIET_MOVES);
    Move move2 = CREATE_MOVE(H1, A1, WHITE_QUEEN, QUIET_MOVES);
    Move move3 = CREATE_MOVE(A1, A8, WHITE_QUEEN, QUIET_MOVES);
    Move move4 = CREATE_MOVE(H8, H1, WHITE_QUEEN, QUIET_MOVES);
    
    TEST_ASSERT_EQUAL(A8, GET_SOURCE_SQUARE_FROM_MOVE(move1));
    TEST_ASSERT_EQUAL(H8, GET_DESTINATION_SQUARE_FROM_MOVE(move1));
    TEST_ASSERT_EQUAL(H1, GET_SOURCE_SQUARE_FROM_MOVE(move2));
    TEST_ASSERT_EQUAL(A1, GET_DESTINATION_SQUARE_FROM_MOVE(move2));
    TEST_ASSERT_EQUAL(A1, GET_SOURCE_SQUARE_FROM_MOVE(move3));
    TEST_ASSERT_EQUAL(A8, GET_DESTINATION_SQUARE_FROM_MOVE(move3));
    TEST_ASSERT_EQUAL(H8, GET_SOURCE_SQUARE_FROM_MOVE(move4));
    TEST_ASSERT_EQUAL(H1, GET_DESTINATION_SQUARE_FROM_MOVE(move4));
}

// Test that moves don't interfere with each other (bit isolation)
void test_CREATE_MOVE_should_isolate_bit_fields(void)
{
    Move move = CREATE_MOVE(B3, G7, BLACK_QUEEN, CAPTURE);
    
    // Check that each field is correctly isolated
    Square source = GET_SOURCE_SQUARE_FROM_MOVE(move);
    Square dest = GET_DESTINATION_SQUARE_FROM_MOVE(move);
    PieceType piece = GET_PIECE_TYPE_FROM_MOVE(move);
    MoveType moveType = GET_MOVE_TYPE_FROM_MOVE(move);
    
    TEST_ASSERT_EQUAL(B3, source);
    TEST_ASSERT_EQUAL(G7, dest);
    TEST_ASSERT_EQUAL(BLACK_QUEEN, piece);
    TEST_ASSERT_EQUAL(CAPTURE, moveType);
    
    // Verify raw bit representation
    TEST_ASSERT_EQUAL(B3, move & SOURCE_SQUARE_MASK);
    TEST_ASSERT_EQUAL(G7 << 6, move & DESTINATION_SQUARE_MASK);
    TEST_ASSERT_EQUAL(BLACK_QUEEN << 12, move & PIECE_TYPE_MASK);
    TEST_ASSERT_EQUAL(CAPTURE << 16, move & MOVE_TYPE_MASK);
}

// Test edge case: same source and destination
void test_CREATE_MOVE_should_handle_same_source_and_destination(void)
{
    Move move = CREATE_MOVE(D4, D4, WHITE_KING, QUIET_MOVES);
    
    TEST_ASSERT_EQUAL(D4, GET_SOURCE_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(D4, GET_DESTINATION_SQUARE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(WHITE_KING, GET_PIECE_TYPE_FROM_MOVE(move));
    TEST_ASSERT_EQUAL(QUIET_MOVES, GET_MOVE_TYPE_FROM_MOVE(move));
}

// Test move equality
void test_CREATE_MOVE_should_create_identical_moves_for_identical_parameters(void)
{
    Move move1 = CREATE_MOVE(E4, E5, WHITE_PAWN, QUIET_MOVES);
    Move move2 = CREATE_MOVE(E4, E5, WHITE_PAWN, QUIET_MOVES);
    
    TEST_ASSERT_EQUAL(move1, move2);
}

// Test move inequality
void test_CREATE_MOVE_should_create_different_moves_for_different_parameters(void)
{
    Move move1 = CREATE_MOVE(E4, E5, WHITE_PAWN, QUIET_MOVES);
    Move move2 = CREATE_MOVE(E4, E5, WHITE_PAWN, CAPTURE);
    Move move3 = CREATE_MOVE(E4, E5, WHITE_KNIGHT, QUIET_MOVES);
    Move move4 = CREATE_MOVE(E4, F5, WHITE_PAWN, QUIET_MOVES);
    Move move5 = CREATE_MOVE(D4, E5, WHITE_PAWN, QUIET_MOVES);
    
    TEST_ASSERT_NOT_EQUAL(move1, move2);
    TEST_ASSERT_NOT_EQUAL(move1, move3);
    TEST_ASSERT_NOT_EQUAL(move1, move4);
    TEST_ASSERT_NOT_EQUAL(move1, move5);
}

void test_make_move_should_make_white_pawn_double_push(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << E2; // Place a white pawn on E2
    game.turn = WHITE;

    Move move = CREATE_MOVE(E2, E4, WHITE_PAWN, DOUBLE_PAWN_PUSH);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << E2)); // Pawn should no longer be on E2
    TEST_ASSERT_EQUAL(1ULL << E4, game.white_pawns & (1ULL << E4)); // Pawn should be on E4
    TEST_ASSERT_EQUAL(E3, game.en_passant_target_square); // En passant target should be set to E3
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn); // Turn should switch to black
}

void test_make_move_should_make_black_pawn_double_push(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << E7; // Place a black pawn on E7
    game.turn = BLACK;

    Move move = CREATE_MOVE(E7, E5, BLACK_PAWN, DOUBLE_PAWN_PUSH);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << E7)); // Pawn should no longer be on E7
    TEST_ASSERT_EQUAL(1ULL << E5, game.black_pawns & (1ULL << E5)); // Pawn should be on E5
    TEST_ASSERT_EQUAL(E6, game.en_passant_target_square); // En passant target should be set to E6
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn); // Turn should switch to white
}

void test_make_move_should_make_white_pawn_quiet_move(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << E4; // Place a white pawn on E4
    game.turn = WHITE;

    Move move = CREATE_MOVE(E4, E5, WHITE_PAWN, QUIET_MOVES);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << E4)); // Pawn should no longer be on E4
    TEST_ASSERT_EQUAL(1ULL << E5, game.white_pawns & (1ULL << E5)); // Pawn should be on E5
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square); // En passant target should be reset
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn); // Turn should switch to black
}

void test_make_move_should_make_black_pawn_quiet_move(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << E5; // Place a black pawn on E5
    game.turn = BLACK;

    Move move = CREATE_MOVE(E5, E4, BLACK_PAWN, QUIET_MOVES);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << E5)); // Pawn should no longer be on E5
    TEST_ASSERT_EQUAL(1ULL << E4, game.black_pawns & (1ULL << E4)); // Pawn should be on E4
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square); // En passant target should be reset
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn); // Turn should switch to white
}

void test_make_move_should_make_white_pawn_capture(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << E4; // Place a white pawn on E4
    game.black_pawns = 1ULL << D5; // Place a black pawn on D5
    game.turn = WHITE;

    Move move = CREATE_MOVE(E4, D5, WHITE_PAWN, CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << E4)); // White pawn should no longer be on E4
    TEST_ASSERT_EQUAL(1ULL << D5, game.white_pawns & (1ULL << D5)); // White pawn should be on D5
    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << D5)); // Black pawn should be captured
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square); // En passant target should be reset
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn); // Turn should switch to black
}


void test_make_move_should_make_white_pawn_capture_on_bishop(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << E4; // Place a white pawn on E4
    game.black_bishops = 1ULL << D5; // Place a black bishop on D5
    game.turn = WHITE;

    Move move = CREATE_MOVE(E4, D5, WHITE_PAWN, CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << E4)); // White pawn should no longer be on E4
    TEST_ASSERT_EQUAL(1ULL << D5, game.white_pawns & (1ULL << D5)); // White pawn should be on D5
    TEST_ASSERT_EQUAL(0ULL, game.black_bishops & (1ULL << D5)); // Black bishop should be captured
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square); // En passant target should be reset
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn); // Turn should switch to black
}

void test_make_move_should_make_black_pawn_capture(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << E5; // Place un pion noir sur E5
    game.white_pawns = 1ULL << D4; // Place un pion blanc sur D4
    game.turn = BLACK;

    Move move = CREATE_MOVE(E5, D4, BLACK_PAWN, CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << E5)); // Le pion noir ne doit plus être sur E5
    TEST_ASSERT_EQUAL(1ULL << D4, game.black_pawns & (1ULL << D4)); // Le pion noir doit être sur D4
    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << D4)); // Le pion blanc doit être capturé
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square); // La cible En Passant doit être réinitialisée
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn); // Le tour doit passer à blanc
}

void test_make_move_should_make_black_pawn_capture_on_bishop(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << E5; // Place un pion noir sur E5
    game.white_bishops = 1ULL << D4; // Place un fou blanc sur D4
    game.turn = BLACK;

    Move move = CREATE_MOVE(E5, D4, BLACK_PAWN, CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << E5)); // Le pion noir ne doit plus être sur E5
    TEST_ASSERT_EQUAL(1ULL << D4, game.black_pawns & (1ULL << D4)); // Le pion noir doit être sur D4
    TEST_ASSERT_EQUAL(0ULL, game.white_bishops & (1ULL << D4)); // Le fou blanc doit être capturé
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square); // La cible En Passant doit être réinitialisée
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn); // Le tour doit passer à blanc
}

void test_make_move_should_make_white_pawn_en_passant_capture(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << E5; // Pion blanc sur E5
    game.black_pawns = 1ULL << D5; // Pion noir sur D5 (pion à capturer)
    game.turn = WHITE;
    game.en_passant_target_square = D6; // La cible En Passant est D6 (case vide après le déplacement double)

    Move move = CREATE_MOVE(E5, D6, WHITE_PAWN, EN_PASSANT_CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << E5)); // Le pion blanc ne doit plus être sur E5
    TEST_ASSERT_EQUAL(1ULL << D6, game.white_pawns & (1ULL << D6)); // Le pion blanc doit être sur D6
    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << D5)); // Le pion noir capturé (en D5) doit être retiré
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square); // La cible En Passant doit être réinitialisée
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn); // Le tour doit passer à noir
}

void test_make_move_should_make_black_pawn_en_passant_capture(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << E4; // Pion noir sur E4
    game.white_pawns = 1ULL << D4; // Pion blanc sur D4 (pion à capturer)
    game.turn = BLACK;
    game.en_passant_target_square = D3; // La cible En Passant est D3

    Move move = CREATE_MOVE(E4, D3, BLACK_PAWN, EN_PASSANT_CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << E4)); // Le pion noir ne doit plus être sur E4
    TEST_ASSERT_EQUAL(1ULL << D3, game.black_pawns & (1ULL << D3)); // Le pion noir doit être sur D3
    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << D4)); // Le pion blanc capturé (en D4) doit être retiré
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square); // La cible En Passant doit être réinitialisée
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn); // Le tour doit passer à blanc
}

void test_make_move_should_make_white_pawn_promotion_to_queen_quiet_move(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << E7; // Pion blanc sur E7
    game.turn = WHITE;

    Move move = CREATE_MOVE(E7, E8, WHITE_PAWN, QUEEN_PROMOTION);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << E7)); // Le pion ne doit plus être sur E7
    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << E8)); // Le pion ne doit pas être sur E8
    TEST_ASSERT_EQUAL(1ULL << E8, game.white_queens & (1ULL << E8)); // La Dame doit être sur E8
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square);
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn);
}

void test_make_move_should_make_black_pawn_promotion_to_knight_capture(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << E2; // Pion noir sur E2
    game.white_rooks = 1ULL << D1; // Tour blanche à capturer sur D1
    game.turn = BLACK;

    Move move = CREATE_MOVE(E2, D1, BLACK_PAWN, KNIGHT_PROMOTION_CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << E2)); // Le pion ne doit plus être sur E2
    TEST_ASSERT_EQUAL(0ULL, game.white_rooks & (1ULL << D1)); // La Tour blanche doit être capturée
    TEST_ASSERT_EQUAL(1ULL << D1, game.black_knights & (1ULL << D1)); // Le Cavalier noir doit être sur D1
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square);
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn);
}

// Promotion tranquille en Tour (ROOK_PROMOTION)
void test_make_move_should_make_white_pawn_promotion_to_rook_quiet_move(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << H7;
    game.turn = WHITE;

    Move move = CREATE_MOVE(H7, H8, WHITE_PAWN, ROOK_PROMOTION);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << H7));
    TEST_ASSERT_EQUAL(1ULL << H8, game.white_rooks & (1ULL << H8)); // Vérifie la Tour
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn);
}

// Promotion tranquille en Fou (BISHOP_PROMOTION)
void test_make_move_should_make_white_pawn_promotion_to_bishop_quiet_move(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << A7;
    game.turn = WHITE;

    Move move = CREATE_MOVE(A7, A8, WHITE_PAWN, BISHOP_PROMOTION);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << A7));
    TEST_ASSERT_EQUAL(1ULL << A8, game.white_bishops & (1ULL << A8)); // Vérifie le Fou
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn);
}

// Promotion tranquille en Cavalier (KNIGHT_PROMOTION)
void test_make_move_should_make_white_pawn_promotion_to_knight_quiet_move(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << B7;
    game.turn = WHITE;

    Move move = CREATE_MOVE(B7, B8, WHITE_PAWN, KNIGHT_PROMOTION);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << B7));
    TEST_ASSERT_EQUAL(1ULL << B8, game.white_knights & (1ULL << B8)); // Vérifie le Cavalier
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn);
}

void test_make_move_should_make_white_pawn_promotion_to_queen_capture(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << G7;
    game.black_rooks = 1ULL << H8; // Pièce à capturer
    game.turn = WHITE;

    Move move = CREATE_MOVE(G7, H8, WHITE_PAWN, QUEEN_PROMOTION_CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << G7));
    TEST_ASSERT_EQUAL(0ULL, game.black_rooks & (1ULL << H8)); // La pièce noire est capturée
    TEST_ASSERT_EQUAL(1ULL << H8, game.white_queens & (1ULL << H8)); // La Dame est placée
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn);
}

// Promotion avec capture en Tour (ROOK_PROMOTION_CAPTURE)
void test_make_move_should_make_white_pawn_promotion_to_rook_capture(void)
{
    Game game = {0};
    game.white_pawns = 1ULL << B7;
    game.black_knights = 1ULL << A8; // Pièce à capturer
    game.turn = WHITE;

    Move move = CREATE_MOVE(B7, A8, WHITE_PAWN, ROOK_PROMOTION_CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.white_pawns & (1ULL << B7));
    TEST_ASSERT_EQUAL(0ULL, game.black_knights & (1ULL << A8)); // Le Cavalier est capturé
    TEST_ASSERT_EQUAL(1ULL << A8, game.white_rooks & (1ULL << A8)); // La Tour est placée
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn);
}

void test_make_move_should_make_black_pawn_promotion_to_queen_quiet_move(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << E2; // Pion noir sur E2
    game.turn = BLACK;

    Move move = CREATE_MOVE(E2, E1, BLACK_PAWN, QUEEN_PROMOTION);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << E2));
    TEST_ASSERT_EQUAL(1ULL << E1, game.black_queens & (1ULL << E1)); // Vérifie la Dame noire
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn);
}

// Promotion tranquille en Cavalier Noir (KNIGHT_PROMOTION)
void test_make_move_should_make_black_pawn_promotion_to_knight_quiet_move(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << G2; // Pion noir sur G2
    game.turn = BLACK;

    Move move = CREATE_MOVE(G2, G1, BLACK_PAWN, KNIGHT_PROMOTION);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << G2));
    TEST_ASSERT_EQUAL(1ULL << G1, game.black_knights & (1ULL << G1)); // Vérifie le Cavalier noir
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn);
}

void test_make_move_should_make_black_pawn_promotion_to_rook_capture(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << D2;
    game.white_bishops = 1ULL << E1; // Pièce blanche à capturer
    game.turn = BLACK;

    Move move = CREATE_MOVE(D2, E1, BLACK_PAWN, ROOK_PROMOTION_CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << D2));
    TEST_ASSERT_EQUAL(0ULL, game.white_bishops & (1ULL << E1)); // Le Fou est capturé
    TEST_ASSERT_EQUAL(1ULL << E1, game.black_rooks & (1ULL << E1)); // La Tour noire est placée
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn);
}

// Promotion avec capture en Fou Noir (BISHOP_PROMOTION_CAPTURE)
void test_make_move_should_make_black_pawn_promotion_to_bishop_capture(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << B2;
    game.white_queens = 1ULL << A1; // Pièce blanche à capturer
    game.turn = BLACK;

    Move move = CREATE_MOVE(B2, A1, BLACK_PAWN, BISHOP_PROMOTION_CAPTURE);
    game = make_move(game, move);

    TEST_ASSERT_EQUAL(0ULL, game.black_pawns & (1ULL << B2));
    TEST_ASSERT_EQUAL(0ULL, game.white_queens & (1ULL << A1)); // La Dame est capturée
    TEST_ASSERT_EQUAL(1ULL << A1, game.black_bishops & (1ULL << A1)); // Le Fou noir est placé
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn);
}

void test_make_move_should_make_white_king_castle_king_side(void)
{
    Game game = {0};
    game.white_king = 1ULL << E1;  // Roi blanc sur E1
    game.white_rooks = 1ULL << H1;  // Tour blanche sur H1
    game.turn = WHITE;
    game.castling_rights = 15; // Supposons une variable pour les droits de roque

    Move move = CREATE_MOVE(E1, G1, WHITE_KING, KING_CASTLE);
    game = make_move(game, move);

    // Vérification du déplacement du Roi : E1 -> G1
    TEST_ASSERT_EQUAL(0ULL, game.white_king & (1ULL << E1));
    TEST_ASSERT_EQUAL(1ULL << G1, game.white_king & (1ULL << G1));
    
    // Vérification du déplacement de la Tour : H1 -> F1
    TEST_ASSERT_EQUAL(0ULL, game.white_rooks & (1ULL << H1));
    TEST_ASSERT_EQUAL(1ULL << F1, game.white_rooks & (1ULL << F1));
    
    // Vérification de la mise à jour des droits de roque (doivent être révoqués pour le Blanc)
    // Le roque côté Roi blanc (et sans doute côté Dame blanc) ne devrait plus être possible.
    TEST_ASSERT_FALSE(game.castling_rights & WHITE_KING_SIDE_CASTLING); 
    TEST_ASSERT_FALSE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square);
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn);
}

void test_make_move_should_make_white_king_castle_queen_side(void)
{
    Game game = {0};
    game.white_king = 1ULL << E1;  // Roi blanc sur E1
    game.white_rooks = 1ULL << A1;  // Tour blanche sur A1
    game.turn = WHITE;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(E1, C1, WHITE_KING, QUEEN_CASTLE);
    game = make_move(game, move);

    // Vérification du déplacement du Roi : E1 -> C1
    TEST_ASSERT_EQUAL(0ULL, game.white_king & (1ULL << E1));
    TEST_ASSERT_EQUAL(1ULL << C1, game.white_king & (1ULL << C1));
    
    // Vérification du déplacement de la Tour : A1 -> D1
    TEST_ASSERT_EQUAL(0ULL, game.white_rooks & (1ULL << A1));
    TEST_ASSERT_EQUAL(1ULL << D1, game.white_rooks & (1ULL << D1));
    
    // Vérification de la mise à jour des droits de roque
    TEST_ASSERT_FALSE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square);
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn);
}

void test_make_move_should_make_black_king_castle_king_side(void)
{
    Game game = {0};
    game.black_king = 1ULL << E8;  // Roi noir sur E8
    game.black_rooks = 1ULL << H8;  // Tour noire sur H8
    game.turn = BLACK;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(E8, G8, BLACK_KING, KING_CASTLE);
    game = make_move(game, move);

    // Vérification du déplacement du Roi : E8 -> G8
    TEST_ASSERT_EQUAL(0ULL, game.black_king & (1ULL << E8));
    TEST_ASSERT_EQUAL(1ULL << G8, game.black_king & (1ULL << G8));
    
    // Vérification du déplacement de la Tour : H8 -> F8
    TEST_ASSERT_EQUAL(0ULL, game.black_rooks & (1ULL << H8));
    TEST_ASSERT_EQUAL(1ULL << F8, game.black_rooks & (1ULL << F8));
    
    // Vérification de la mise à jour des droits de roque
    TEST_ASSERT_FALSE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
    
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square);
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn);
}

void test_make_move_should_make_black_king_castle_queen_side(void)
{
    Game game = {0};
    game.black_king = 1ULL << E8;  // Roi noir sur E8
    game.black_rooks = 1ULL << A8;  // Tour noire sur A8
    game.turn = BLACK;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(E8, C8, BLACK_KING, QUEEN_CASTLE);
    game = make_move(game, move);

    // Vérification du déplacement du Roi : E8 -> C8
    TEST_ASSERT_EQUAL(0ULL, game.black_king & (1ULL << E8));
    TEST_ASSERT_EQUAL(1ULL << C8, game.black_king & (1ULL << C8));
    
    // Vérification du déplacement de la Tour : A8 -> D8
    TEST_ASSERT_EQUAL(0ULL, game.black_rooks & (1ULL << A8));
    TEST_ASSERT_EQUAL(1ULL << D8, game.black_rooks & (1ULL << D8));
    
    // Vérification de la mise à jour des droits de roque
    TEST_ASSERT_FALSE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
    
    TEST_ASSERT_EQUAL(-1, game.en_passant_target_square);
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn);
}

void test_make_move_should_revoke_white_castling_rights_when_white_king_moves(void)
{
    Game game = {0};
    game.white_king = 1ULL << E1; // Roi blanc sur E1
    game.turn = WHITE;
    game.castling_rights = 15; // Tous les droits sont actifs

    Move move = CREATE_MOVE(E1, D1, WHITE_KING, QUIET_MOVES); // Mouvement tranquille du Roi
    game = make_move(game, move);

    // Les droits de roque blancs doivent être révoqués
    TEST_ASSERT_FALSE(game.castling_rights & WHITE_KING_SIDE_CASTLING); 
    TEST_ASSERT_FALSE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    
    // Les droits de roque noirs doivent rester intacts
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
    
    TEST_ASSERT_EQUAL(BLACK_TURN, game.turn);
}

void test_make_move_should_revoke_black_castling_rights_when_black_king_moves(void)
{
    Game game = {0};
    game.black_king = 1ULL << E8; // Roi noir sur E8
    game.turn = BLACK;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(E8, D8, BLACK_KING, QUIET_MOVES); // Mouvement tranquille du Roi
    game = make_move(game, move);

    // Les droits de roque noirs doivent être révoqués
    TEST_ASSERT_FALSE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
    TEST_ASSERT_FALSE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
    
    // Les droits de roque blancs doivent rester intacts
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    
    TEST_ASSERT_EQUAL(WHITE_TURN, game.turn);
}

void test_make_move_should_revoke_white_kingside_castling_when_h1_rook_moves(void)
{
    Game game = {0};
    game.white_rooks = 1ULL << H1; // Tour blanche sur H1
    game.turn = WHITE;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(H1, H2, WHITE_ROOK, QUIET_MOVES);
    game = make_move(game, move);

    // Droit K-side Blanc révoqué
    TEST_ASSERT_FALSE(game.castling_rights & WHITE_KING_SIDE_CASTLING); 
    
    // Les autres droits doivent rester intacts
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
}

void test_make_move_should_revoke_white_queenside_castling_when_a1_rook_moves(void)
{
    Game game = {0};
    game.white_rooks = 1ULL << A1; // Tour blanche sur A1
    game.turn = WHITE;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(A1, A2, WHITE_ROOK, QUIET_MOVES);
    game = make_move(game, move);

    // Droit Q-side Blanc révoqué
    TEST_ASSERT_FALSE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    
    // Les autres droits doivent rester intacts
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
}

void test_make_move_should_revoke_black_kingside_castling_when_h8_rook_moves(void)
{
    Game game = {0};
    game.black_rooks = 1ULL << H8; // Tour noire sur H8
    game.turn = BLACK;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(H8, H7, BLACK_ROOK, QUIET_MOVES);
    game = make_move(game, move);

    // Droit K-side Noir révoqué
    TEST_ASSERT_FALSE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
    
    // Les autres droits doivent rester intacts
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
}

void test_make_move_should_revoke_black_queenside_castling_when_a8_rook_moves(void)
{
    Game game = {0};
    game.black_rooks = 1ULL << A8; // Tour noire sur A8
    game.turn = BLACK;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(A8, A7, BLACK_ROOK, QUIET_MOVES);
    game = make_move(game, move);

    // Droit Q-side Noir révoqué
    TEST_ASSERT_FALSE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
    
    // Les autres droits doivent rester intacts
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
}

void test_make_move_should_revoke_white_kingside_castling_when_h1_rook_is_captured(void)
{
    Game game = {0};
    game.black_pawns = 1ULL << G2; // Pièce attaquante noire
    game.white_rooks = 1ULL << H1; // Tour blanche sur H1
    game.turn = BLACK;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(G2, H1, BLACK_PAWN, CAPTURE);
    game = make_move(game, move);

    // Droit K-side Blanc révoqué
    TEST_ASSERT_FALSE(game.castling_rights & WHITE_KING_SIDE_CASTLING); 
    
    // Les autres droits doivent rester intacts
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
}

void test_make_move_should_revoke_white_queenside_castling_when_a1_rook_is_captured(void)
{
    Game game = {0};
    game.black_knights = 1ULL << B3; // Pièce attaquante noire
    game.white_rooks = 1ULL << A1; // Tour blanche sur A1
    game.turn = BLACK;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(B3, A1, BLACK_KNIGHT, CAPTURE); // Attention: Le type de pièce dans la Move est l'ATTAQUANT
    game = make_move(game, move);

    // Droit Q-side Blanc révoqué
    TEST_ASSERT_FALSE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING); 
    
    // Les autres droits doivent rester intacts
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
}

void test_make_move_should_revoke_black_kingside_castling_when_h8_rook_is_captured(void)
{
    Game game = {0};
    game.white_bishops = 1ULL << F6; // Pièce attaquante blanche
    game.black_rooks = 1ULL << H8; // Tour noire sur H8
    game.turn = WHITE;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(F6, H8, WHITE_BISHOP, CAPTURE);
    game = make_move(game, move);

    // Droit K-side Noir révoqué
    TEST_ASSERT_FALSE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
    
    // Les autres droits doivent rester intacts
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
}

void test_make_move_should_revoke_black_queenside_castling_when_a8_rook_is_captured(void)
{
    Game game = {0};
    game.white_rooks = 1ULL << A4; // Pièce attaquante blanche
    game.black_rooks = 1ULL << A8; // Tour noire sur A8
    game.turn = WHITE;
    game.castling_rights = 15;

    Move move = CREATE_MOVE(A4, A8, WHITE_ROOK, CAPTURE);
    game = make_move(game, move);

    // Droit Q-side Noir révoqué
    TEST_ASSERT_FALSE(game.castling_rights & BLACK_QUEEN_SIDE_CASTLING);
    
    // Les autres droits doivent rester intacts
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_KING_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & WHITE_QUEEN_SIDE_CASTLING);
    TEST_ASSERT_TRUE(game.castling_rights & BLACK_KING_SIDE_CASTLING);
}
// #endif // TEST
