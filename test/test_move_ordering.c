

#include "unity.h"

#include "move_ordering.h"
#include "move_generator.h"
#include "moves.h"
#include "board.h"
#include "game.h"
#include "pieces.h"
#include "binary_tools.h"
#include "king_moves.h"
#include "knights_moves.h"
#include "pawns_moves.h"
#include "bishops_moves.h"
#include "rooks_moves.h"
#include "queens_moves.h"
#include "test_helpers.h"
#include "zobrist_key.h"

void setUp(void)
{
    initialize_magic_zobrist_numbers();
    initialize_move_generation_databases();
}

void tearDown(void)
{
}

// ============================================================================
// TESTS UNITAIRES: Vérification de la table MVV-LVA
// ============================================================================

void test_mvv_lva_table_pawn_captures_queen_highest_score(void)
{
    // Un pion qui capture une dame devrait avoir le score le plus élevé (506)
    TEST_ASSERT_EQUAL_INT(506, score_mvv_lva[0][4]); // Pawn captures Queen
}

void test_mvv_lva_table_queen_captures_pawn_lowest_score(void)
{
    // Une dame qui capture un pion devrait avoir un score faible (102)
    TEST_ASSERT_EQUAL_INT(102, score_mvv_lva[4][0]); // Queen captures Pawn
}

void test_mvv_lva_table_pawn_captures_pawn(void)
{
    // Pion capture pion
    TEST_ASSERT_EQUAL_INT(106, score_mvv_lva[0][0]); // Pawn captures Pawn
}

void test_mvv_lva_table_knight_captures_rook(void)
{
    // Cavalier capture tour
    TEST_ASSERT_EQUAL_INT(405, score_mvv_lva[1][3]); // Knight captures Rook
}

void test_mvv_lva_table_bishop_captures_queen(void)
{
    // Fou capture dame
    TEST_ASSERT_EQUAL_INT(504, score_mvv_lva[2][4]); // Bishop captures Queen
}

// ============================================================================
// TESTS: order_move avec positions simples
// ============================================================================

void test_order_move_with_single_capture_pawn_takes_queen(void)
{
    // Position où un pion blanc peut capturer une dame noire
    // Pion blanc en D4, Dame noire en E5
    char *position = "8/8/8/4q3/3P4/8/8/4K2k w - - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* move_list = (MoveList*) malloc(sizeof(MoveList));
    move_list->current_index = 0;

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);
    order_move(game, move_list, 0);

    // Le premier coup devrait être la capture PxQ (score 506)
    int found_pawn_captures_queen = 0;
    Move first_move = move_list->moves[0].move;
    TEST_ASSERT_EQUAL_INT(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(E5, GET_DESTINATION_SQUARE_FROM_MOVE(first_move));

    free_game(game);
    free(move_list);
}

void test_order_move_with_multiple_captures_different_victims(void)
{
    // Position avec plusieurs captures possibles:
    // Cavalier blanc en E4 peut capturer: Pion noir en D6, Tour noire en F6
    // Le cavalier devrait préférer capturer la tour (405) au pion (105)
    char *position = "8/8/3p1r2/8/4N3/8/8/4K2k w - - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* move_list = (MoveList*) malloc(sizeof(MoveList));
    move_list->current_index = 0;

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);
    order_move(game, move_list, 0);

    // Le premier coup devrait être NxR (405)
    Move first_move = move_list->moves[0].move;
    TEST_ASSERT_EQUAL_INT(WHITE_KNIGHT, GET_PIECE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(F6, GET_DESTINATION_SQUARE_FROM_MOVE(first_move));

    // Le deuxième coup devrait être NxP (105)
    Move second_move = move_list->moves[1].move;
    TEST_ASSERT_EQUAL_INT(WHITE_KNIGHT, GET_PIECE_TYPE_FROM_MOVE(second_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(second_move));
    TEST_ASSERT_EQUAL_INT(D6, GET_DESTINATION_SQUARE_FROM_MOVE(second_move));

    free_game(game);
    free(move_list);
}

void test_order_move_with_multiple_attackers_same_victim(void)
{
    // Position où plusieurs pièces peuvent capturer la même cible (dame noire en E5):
    // Pion blanc D4 -> PxQ (506)
    // Cavalier blanc C4 -> NxQ (505)
    // Fou blanc G3 -> BxQ (504)
    // Le pion devrait capturer en premier (score le plus élevé avec MVV-LVA)
    char *position = "8/8/8/4q3/2NP4/6B1/8/4K2k w - - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* move_list = (MoveList*) malloc(sizeof(MoveList));
    move_list->current_index = 0;

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);
    order_move(game, move_list, 0);

    // Le premier coup devrait être PxQ (506)
    Move first_move = move_list->moves[0].move;
    TEST_ASSERT_EQUAL_INT(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(E5, GET_DESTINATION_SQUARE_FROM_MOVE(first_move));

    // Le deuxième coup devrait être NxQ (505)
    Move second_move = move_list->moves[1].move;
    TEST_ASSERT_EQUAL_INT(WHITE_KNIGHT, GET_PIECE_TYPE_FROM_MOVE(second_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(second_move));
    TEST_ASSERT_EQUAL_INT(E5, GET_DESTINATION_SQUARE_FROM_MOVE(second_move));

    // Le troisième coup devrait être BxQ (504)
    Move third_move = move_list->moves[2].move;
    TEST_ASSERT_EQUAL_INT(WHITE_BISHOP, GET_PIECE_TYPE_FROM_MOVE(third_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(third_move));
    TEST_ASSERT_EQUAL_INT(E5, GET_DESTINATION_SQUARE_FROM_MOVE(third_move));

    free_game(game);
    free(move_list);
}

void test_order_move_captures_before_quiet_moves(void)
{
    // Position simple: Cavalier blanc en E4, Pion noir en F6
    // Les captures devraient être ordonnées avant les coups quiets
    char *position = "8/8/5p2/8/4N3/8/8/4K2k w - - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* move_list = (MoveList*) malloc(sizeof(MoveList));
    move_list->current_index = 0;

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);
    order_move(game, move_list, 0);

    // Le premier coup devrait être NxP (105)
    Move first_move = move_list->moves[0].move;
    TEST_ASSERT_EQUAL_INT(WHITE_KNIGHT, GET_PIECE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(F6, GET_DESTINATION_SQUARE_FROM_MOVE(first_move));

    free_game(game);
    free(move_list);
}

// ============================================================================
// TESTS: Positions complexes avec multiples captures
// ============================================================================

void test_order_move_tricky_position_white(void)
{
    // Position "tricky" avec plusieurs captures possibles pour les blancs
    char *position = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K w kq - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* move_list = (MoveList*) malloc(sizeof(MoveList));
    move_list->current_index = 0;

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);
    order_move(game, move_list, 0);

    // Verification par victime capturée

    // Fou blanc capture dame noire (504)
    Move first_move = move_list->moves[0].move;
    TEST_ASSERT_EQUAL_INT(WHITE_BISHOP, GET_PIECE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(A3, GET_DESTINATION_SQUARE_FROM_MOVE(first_move));

    // Cavalier blanc capture tour noire (405)
    Move second_move = move_list->moves[1].move;
    TEST_ASSERT_EQUAL_INT(WHITE_KNIGHT, GET_PIECE_TYPE_FROM_MOVE(second_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(second_move));
    TEST_ASSERT_EQUAL_INT(H8, GET_DESTINATION_SQUARE_FROM_MOVE(second_move));

    // fou blanc capture cavalier noir (204)
    Move third_move = move_list->moves[2].move;
    TEST_ASSERT_EQUAL_INT(WHITE_BISHOP, GET_PIECE_TYPE_FROM_MOVE(third_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(third_move));
    TEST_ASSERT_EQUAL_INT(A5, GET_DESTINATION_SQUARE_FROM_MOVE(third_move));

    free_game(game);
    free(move_list);
}

void test_order_move_tricky_position_black(void)
{
    // Position "tricky" avec plusieurs captures possibles pour les noirs
    char *position = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K b kq - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* move_list = (MoveList*) malloc(sizeof(MoveList));
    move_list->current_index = 0;

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);
    order_move(game, move_list, 0);

    // Verification par victime capturée

    // Poin noir capture tour blanche (406)
    Move first_move = move_list->moves[0].move;
    TEST_ASSERT_EQUAL_INT(BLACK_PAWN, GET_PIECE_TYPE_FROM_MOVE(first_move));
    // Attention promotion avec capture
    int is_promotion_capture = GET_MOVE_TYPE_FROM_MOVE(first_move) == QUEEN_PROMOTION_CAPTURE ||
                               GET_MOVE_TYPE_FROM_MOVE(first_move) == ROOK_PROMOTION_CAPTURE ||
                               GET_MOVE_TYPE_FROM_MOVE(first_move) == BISHOP_PROMOTION_CAPTURE ||
                               GET_MOVE_TYPE_FROM_MOVE(first_move) == KNIGHT_PROMOTION_CAPTURE;
    TEST_ASSERT_TRUE(is_promotion_capture);
    TEST_ASSERT_EQUAL_INT(A1, GET_DESTINATION_SQUARE_FROM_MOVE(first_move));

    // Attention ici gape de 4 coups

    // Dame noire capture fou blanc (302)
    Move second_move = move_list->moves[4].move;
    TEST_ASSERT_EQUAL_INT(BLACK_QUEEN, GET_PIECE_TYPE_FROM_MOVE(second_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(second_move));
    TEST_ASSERT_EQUAL(1, GET_DESTINATION_SQUARE_FROM_MOVE(second_move) == B4 || GET_DESTINATION_SQUARE_FROM_MOVE(second_move) == A4);

    // Attention ici gap de 2 coups

    // Fou noir capture cavalier blanc (204)
    Move third_move = move_list->moves[6].move;
    TEST_ASSERT_EQUAL_INT(BLACK_BISHOP, GET_PIECE_TYPE_FROM_MOVE(third_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(third_move));
    TEST_ASSERT_EQUAL_INT(F7, GET_DESTINATION_SQUARE_FROM_MOVE(third_move));

    // Dame noire capture cavalier blanc (202)
    Move fourth_move = move_list->moves[7].move;
    TEST_ASSERT_EQUAL_INT(BLACK_QUEEN, GET_PIECE_TYPE_FROM_MOVE(fourth_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(fourth_move));
    TEST_ASSERT_EQUAL_INT(F3, GET_DESTINATION_SQUARE_FROM_MOVE(fourth_move));

    // Roi noir capture cavalier blanc (201)
    Move fifth_move = move_list->moves[8].move;
    TEST_ASSERT_EQUAL_INT(BLACK_KING, GET_PIECE_TYPE_FROM_MOVE(fifth_move));
    TEST_ASSERT_EQUAL_INT(CAPTURE, GET_MOVE_TYPE_FROM_MOVE(fifth_move));
    TEST_ASSERT_EQUAL_INT(F7, GET_DESTINATION_SQUARE_FROM_MOVE(fifth_move));

    free_game(game);
    free(move_list);
}

// ============================================================================
// TESTS: Cas spéciaux - promotions avec captures
// ============================================================================

void test_order_move_promotion_captures(void)
{
    // Position où un pion peut promouvoir en capturant
    // Pion blanc en G7, Tour noire en H8
    char *position = "7r/6P1/8/8/8/8/8/4K2k w - - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* move_list = (MoveList*) malloc(sizeof(MoveList));
    move_list->current_index = 0;

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);
    order_move(game, move_list, 0);

    // Le premier coup devrait être la promotion avec capture
    Move first_move = move_list->moves[0].move;
    TEST_ASSERT_EQUAL_INT(WHITE_PAWN, GET_PIECE_TYPE_FROM_MOVE(first_move));
    TEST_ASSERT_EQUAL_INT(H8, GET_DESTINATION_SQUARE_FROM_MOVE(first_move));

    free_game(game);
    free(move_list);
}

void test_add_killer_move_at_ply(void)
{
    Move test_move = CREATE_MOVE(E2, E4, WHITE_PAWN, QUIET_MOVES);
    int ply = 5;

    add_killer_move_at_ply(test_move, ply);

    TEST_ASSERT_EQUAL_UINT(test_move, killer_move[ply][0]);
}

void test_add_two_killer_moves_at_different_plies(void)
{
    Move first_move = CREATE_MOVE(E2, E4, WHITE_PAWN, QUIET_MOVES);
    int first_ply = 3;

    Move second_move = CREATE_MOVE(D7, D5, BLACK_PAWN, QUIET_MOVES);
    int second_ply = 4;

    add_killer_move_at_ply(first_move, first_ply);
    add_killer_move_at_ply(second_move, second_ply);

    // Vérification du premier coup
    TEST_ASSERT_EQUAL_UINT(first_move, killer_move[first_ply][0]);

    // Vérification du deuxième coup
    TEST_ASSERT_EQUAL_UINT(second_move, killer_move[second_ply][0]);
}

void test_add_killer_move_overwrite_previous(void)
{
    Move first_move = CREATE_MOVE(E2, E4, WHITE_PAWN, QUIET_MOVES);
    int ply = 2;

    Move second_move = CREATE_MOVE(E7, E5, BLACK_PAWN, QUIET_MOVES);

    add_killer_move_at_ply(first_move, ply);
    add_killer_move_at_ply(second_move, ply); // Doit écraser le premier

    // Vérification que le deuxième coup a écrasé le premier
    TEST_ASSERT_EQUAL_UINT(second_move, killer_move[ply][0]);

    // Le premier coup doit etre en deuxième position
    TEST_ASSERT_EQUAL_UINT(first_move, killer_move[ply][1]);
}