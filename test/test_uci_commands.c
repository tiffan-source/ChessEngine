
// #ifdef TEST

#include "unity.h"

#include "uci_commands.h"
#include "game.h"
#include "board.h"
#include "standard_lib.h"
#include "moves.h"
#include "move_generator.h"
#include "king_moves.h"
#include "pawns_moves.h"
#include "queens_moves.h"
#include "rooks_moves.h"
#include "bishops_moves.h"
#include "search_and_find.h"
#include "evaluation.h"
#include "knights_moves.h"
#include "binary_tools.h"
#include "pieces.h"

Game* test_game = NULL;

void setUp(void)
{
    initialize_move_generation_databases();
}

void tearDown(void)
{
    if (test_game)
    {
        free_game(test_game);
        test_game = NULL;
    }
}

int are_games_equal(Game* game1, Game* game2)
{
    return (game1->black_pawns == game2->black_pawns) &&
           (game1->black_knights == game2->black_knights) &&
           (game1->black_bishops == game2->black_bishops) &&
           (game1->black_rooks == game2->black_rooks) &&
           (game1->black_queens == game2->black_queens) &&
           (game1->black_king == game2->black_king) &&

           (game1->white_pawns == game2->white_pawns) &&
           (game1->white_knights == game2->white_knights) &&
           (game1->white_bishops == game2->white_bishops) &&
           (game1->white_rooks == game2->white_rooks) &&
           (game1->white_queens == game2->white_queens) &&
           (game1->white_king == game2->white_king) &&

           (game1->turn == game2->turn) &&
           (game1->castling_rights == game2->castling_rights) &&
           (game1->en_passant_target_square == game2->en_passant_target_square);
}

void test_handle_uci_command_should_return_id_name(void)
{
    char response[256] = {0};

    handle_command(&test_game, "uci\n", response);

    TEST_ASSERT_NOT_NULL(response);
    TEST_ASSERT_EQUAL_STRING("id name UpYourChess\nid author BlackGenius\nuciok\n", response);
}

void test_handle_isready_command_should_return_readyok(void)
{
    char response[256] = {0};

    handle_command(&test_game, "isready\n", response);

    TEST_ASSERT_NOT_NULL(response);
    TEST_ASSERT_EQUAL_STRING("readyok\n", response);
}

void test_handle_position_startpos_moves_e2e4_e7e5_command_should_initialize_game(void)
{
    char response[256] = {0};
    Game* expected_game = create_game();

    handle_command(&test_game, "position startpos moves e2e4 e7e5\n", response);

    make_move(expected_game, create_move(E2, E4, WHITE_PAWN, DOUBLE_PAWN_PUSH));
    make_move(expected_game, create_move(E7, E5, BLACK_PAWN, DOUBLE_PAWN_PUSH));

    TEST_ASSERT_NOT_NULL(test_game);
    TEST_ASSERT_TRUE(are_games_equal(test_game, expected_game));

    free_game(expected_game);
}

void test_handle_position_startpos_moves_a2a4_e7e5_command_should_initialize_game(void)
{
    char response[256] = {0};
    Game* expected_game = create_game();

    handle_command(&test_game, "position startpos moves a2a4 e7e5\n", response);

    make_move(expected_game, create_move(A2, A4, WHITE_PAWN, DOUBLE_PAWN_PUSH));
    make_move(expected_game, create_move(E7, E5, BLACK_PAWN, DOUBLE_PAWN_PUSH));

    TEST_ASSERT_NOT_NULL(test_game);
    TEST_ASSERT_TRUE(are_games_equal(test_game, expected_game));

    free_game(expected_game);
}

void test_handle_position_fen_command_should_initialize_game(void)
{
    char response[256] = {0};
    Game* expected_game = create_game_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    handle_command(&test_game, "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1\n", response);

    TEST_ASSERT_NOT_NULL(test_game);
    TEST_ASSERT_TRUE(are_games_equal(test_game, expected_game));

    free_game(expected_game);
}

void test_handle_position_fen_moves_command_should_initialize_game(void)
{
    char response[256] = {0};
    Game* expected_game = create_game_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    make_move(expected_game, create_move(E2, E4, WHITE_PAWN, DOUBLE_PAWN_PUSH));
    make_move(expected_game, create_move(E7, E5, BLACK_PAWN, DOUBLE_PAWN_PUSH));

    handle_command(&test_game, "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 moves e2e4 e7e5\n", response);

    TEST_ASSERT_NOT_NULL(test_game);
    TEST_ASSERT_TRUE(are_games_equal(test_game, expected_game));

    free_game(expected_game);
}

void test_handle_position_tricky_fen_moves_command_should_initialize_game(void)
{
    char response[256] = {0};
    Game* expected_game = create_game_from_FEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");

    make_move(expected_game, create_move(E2, A6, WHITE_BISHOP, CAPTURE));
    make_move(expected_game, create_move(C7, C5, BLACK_PAWN, DOUBLE_PAWN_PUSH));

    handle_command(&test_game, "position fen r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - moves e2a6 c7c5\n", response);

    TEST_ASSERT_NOT_NULL(test_game);
    TEST_ASSERT_TRUE(are_games_equal(test_game, expected_game));

    free_game(expected_game);
}

void test_handle_position_startpos_only_command_should_initialize_game(void)
{
    char response[256] = {0};
    Game* expected_game = create_game(); // Crée la position de départ (FEN : rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1)

    handle_command(&test_game, "position startpos\n", response);

    TEST_ASSERT_NOT_NULL(test_game);
    TEST_ASSERT_TRUE(are_games_equal(test_game, expected_game));

    free_game(expected_game);
}

void test_handle_position_fen_only_command_should_initialize_game_2(void)
{
    // Position du milieu de partie
    const char* tricky_fen = "4r3/8/5R2/8/8/2B5/6PP/7K w - - 0 1";
    char response[256] = {0};
    Game* expected_game = create_game_from_FEN(tricky_fen);

    // Notez l'absence de 'moves'
    char command[256];
    snprintf(command, sizeof(command), "position fen %s\n", tricky_fen);

    handle_command(&test_game, command, response);

    TEST_ASSERT_NOT_NULL(test_game);
    TEST_ASSERT_TRUE(are_games_equal(test_game, expected_game));

    free_game(expected_game);
}

void test_handle_position_startpos_moves_roque_capture_should_update_game_state(void)
{
    char response[256] = {0};
    Game* expected_game = create_game();

    // 1. e4 e5 2. Nf3 Nc6 3. Bc4 Bc5 4. O-O Nf6 5. d4 exd4 6. Nxd4
    handle_command(&test_game, "position startpos moves e2e4 e7e5 g1f3 b8c6 f1c4 f8c5 e1g1 g8f6 d2d4 e5d4 f3d4\n", response);

    // Initialisation manuelle des mouvements attendus
    make_move(expected_game, create_move(E2, E4, WHITE_PAWN, DOUBLE_PAWN_PUSH));
    make_move(expected_game, create_move(E7, E5, BLACK_PAWN, DOUBLE_PAWN_PUSH));
    make_move(expected_game, create_move(G1, F3, WHITE_KNIGHT, QUIET_MOVES));
    make_move(expected_game, create_move(B8, C6, BLACK_KNIGHT, QUIET_MOVES));
    make_move(expected_game, create_move(F1, C4, WHITE_BISHOP, QUIET_MOVES));
    make_move(expected_game, create_move(F8, C5, BLACK_BISHOP, QUIET_MOVES));
    
    // Le roque Blanc : E1 -> G1 (flag ROQUE_COURT)
    make_move(expected_game, create_move(E1, G1, WHITE_KING, KING_CASTLE));
    
    make_move(expected_game, create_move(G8, F6, BLACK_KNIGHT, QUIET_MOVES));
    make_move(expected_game, create_move(D2, D4, WHITE_PAWN, DOUBLE_PAWN_PUSH));
    
    // e5d4 (capture du pion)
    make_move(expected_game, create_move(E5, D4, BLACK_PAWN, CAPTURE)); 
    make_move(expected_game, create_move(F3, D4, WHITE_KNIGHT, CAPTURE));

    TEST_ASSERT_NOT_NULL(test_game);
    TEST_ASSERT_TRUE(are_games_equal(test_game, expected_game));

    free_game(expected_game);
}

void test_handle_position_fen_moves_with_promotion_should_update_game_state(void)
{
    // FEN : Pion Blanc sur d7, prêt à promouvoir
    const char* promotion_fen = "8/P7/8/8/8/8/8/4K3 w - - 0 1";
    char response[256] = {0};
    Game* expected_game = create_game_from_FEN(promotion_fen);

    // Mouvement : a7a8q (Pion a7 vers a8, promotion en Dame)
    handle_command(&test_game, "position fen 8/P7/8/8/8/8/8/4K3 w - - 0 1 moves a7a8q\n", response);

    // Initialisation manuelle du mouvement attendu (flag PROMOTION)
    make_move(expected_game, create_move(A7, A8, WHITE_PAWN, QUEEN_PROMOTION)); 

    TEST_ASSERT_NOT_NULL(test_game);
    TEST_ASSERT_TRUE(are_games_equal(test_game, expected_game));

    free_game(expected_game);
}

void test_handle_position_fen_moves_with_en_passant_should_update_game_state(void)
{
    // FEN : Position où un pion Noir vient de faire un double pas (d5), 
    // et le pion Blanc sur e5 peut le capturer en passant.
    const char* ep_fen = "rnbqkbnr/pppp1ppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1"; // Le trait est aux Noirs
    char response[256] = {0};
    Game* expected_game = create_game_from_FEN(ep_fen);

    // Mouvements : 1... d5 2. exd6 (capture en passant)
    handle_command(&test_game, "position fen rnbqkbnr/pppp1ppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1 moves c7c5 d5c6\n", response);

    // Mouvements manuels :
    // d7d5 est un Double Pawn Push
    make_move(expected_game, create_move(C7, C5, BLACK_PAWN, DOUBLE_PAWN_PUSH));
    
    // e5d6 est une capture En Passant (flag EN_PASSANT)
    make_move(expected_game, create_move(D5, C6, WHITE_PAWN, EN_PASSANT_CAPTURE));

    TEST_ASSERT_NOT_NULL(test_game);
    TEST_ASSERT_TRUE(are_games_equal(test_game, expected_game));

    free_game(expected_game);
}

void test_handle_go_command_should_return_best_moves(void)
{
    char response[256] = {0};
    Game* game = create_game_from_FEN("5k2/2PK1p2/pq6/6Q1/7P/4P3/8/8 b - - 0 1");

    handle_command(&game, "go\n", response);

    TEST_ASSERT_EQUAL_STRING("bestmove b6e6\n", response);

    free_game(game);
}
// #endif // TEST