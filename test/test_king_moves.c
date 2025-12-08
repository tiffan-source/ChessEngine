
#include "unity.h"

#include "king_moves.h"
#include "board.h"
#include "moves.h"
#include "game.h"
#include "binary_tools.h"
#include "bishops_moves.h"
#include "rooks_moves.h"
#include "knights_moves.h"
#include "queens_moves.h"
#include "pieces.h"
#include "pawns_moves.h"


void setUp(void)
{
    initialize_pre_calculated_bishop_moves_database();
    initialize_pre_calculated_rook_moves_database();
    initialize_pre_calculated_pawn_attacks_database();
}

void tearDown(void)
{
}

static int compare_move(const void *a, const void *b) {
    int ia = *(const Move*)a;
    int ib = *(const Move*)b;
    return ia - ib;
}

void test_generate_king_moves_from_a8_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_king_moves_from_square(A8);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, A7);
    expected = SET_BIT_ON_BITBOARD(expected, B7);
    expected = SET_BIT_ON_BITBOARD(expected, B8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_king_moves_from_d5_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_king_moves_from_square(D5);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, C4);
    expected = SET_BIT_ON_BITBOARD(expected, D4);
    expected = SET_BIT_ON_BITBOARD(expected, E4);
    expected = SET_BIT_ON_BITBOARD(expected, C5);
    expected = SET_BIT_ON_BITBOARD(expected, E5);
    expected = SET_BIT_ON_BITBOARD(expected, C6);
    expected = SET_BIT_ON_BITBOARD(expected, D6);
    expected = SET_BIT_ON_BITBOARD(expected, E6);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_generate_king_moves_from_h7_should_return_valid_bitboard(void)
{
    Bitboard moves = generate_king_moves_from_square(H7);
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, G6);
    expected = SET_BIT_ON_BITBOARD(expected, H6);
    expected = SET_BIT_ON_BITBOARD(expected, G7);
    expected = SET_BIT_ON_BITBOARD(expected, G8);
    expected = SET_BIT_ON_BITBOARD(expected, H8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_king_moves_from_h7_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_king_moves[H7];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, G6);
    expected = SET_BIT_ON_BITBOARD(expected, H6);
    expected = SET_BIT_ON_BITBOARD(expected, G7);
    expected = SET_BIT_ON_BITBOARD(expected, G8);
    expected = SET_BIT_ON_BITBOARD(expected, H8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_king_moves_from_c3_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_king_moves[C3];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, B2);
    expected = SET_BIT_ON_BITBOARD(expected, C2);
    expected = SET_BIT_ON_BITBOARD(expected, D2);
    expected = SET_BIT_ON_BITBOARD(expected, B3);
    expected = SET_BIT_ON_BITBOARD(expected, D3);
    expected = SET_BIT_ON_BITBOARD(expected, B4);
    expected = SET_BIT_ON_BITBOARD(expected, C4);
    expected = SET_BIT_ON_BITBOARD(expected, D4);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_king_moves_from_e1_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_king_moves[E1];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, D1);
    expected = SET_BIT_ON_BITBOARD(expected, F1);
    expected = SET_BIT_ON_BITBOARD(expected, D2);
    expected = SET_BIT_ON_BITBOARD(expected, E2);
    expected = SET_BIT_ON_BITBOARD(expected, F2);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}

void test_retrieve_pre_calculated_king_moves_from_h8_should_return_valid_bitboard(void)
{
    Bitboard moves = pre_calculated_king_moves[H8];
    Bitboard expected = 0x0ULL;

    expected = SET_BIT_ON_BITBOARD(expected, G7);
    expected = SET_BIT_ON_BITBOARD(expected, H7);
    expected = SET_BIT_ON_BITBOARD(expected, G8);

    TEST_ASSERT_EQUAL_UINT64(expected, moves);
}


void test_generate_all_white_king_move_from_tricky_position(void)
{
    char *position_white = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K w kq - 0 1";
    
    Game *game_white = create_game_from_FEN(position_white);

    MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
    result_for_white->current_index = 0;

    Move expected_for_white[] = {
        CREATE_MOVE(H1, G1, WHITE_KING, QUIET_MOVES),
        CREATE_MOVE(H1, H2, WHITE_KING, CAPTURE),
    };
    
    generate_all_king_quiet_and_capture_moves_from_game_state(game_white, result_for_white);

    TEST_ASSERT_EQUAL_INT(2, result_for_white->current_index);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_for_white, result_for_white->moves, 2);

    free_game(game_white);
    free(result_for_white);
}


void test_generate_all_black_king_move_from_tricky_position(void)
{
    char *position_black = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1R1K b kq - 0 1";
    
    Game *game_black = create_game_from_FEN(position_black);

    MoveList* result_for_black = (MoveList*) malloc(sizeof(MoveList));
    result_for_black->current_index = 0;


    Move expected_for_black[] = {
        CREATE_MOVE(E8, D8, BLACK_KING, QUIET_MOVES),
        CREATE_MOVE(E8, F8, BLACK_KING, QUIET_MOVES),
        CREATE_MOVE(E8, E7, BLACK_KING, QUIET_MOVES),
        CREATE_MOVE(E8, F7, BLACK_KING, CAPTURE),
    };
    
    generate_all_king_quiet_and_capture_moves_from_game_state(game_black, result_for_black);
    
    qsort(result_for_black->moves, result_for_black->current_index, sizeof(Move), compare_move);
    qsort(expected_for_black, 4, sizeof(Move), compare_move);

    TEST_ASSERT_EQUAL_INT(4, result_for_black->current_index);  
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_for_black, result_for_black->moves, 4);
    free_game(game_black);

    free(result_for_black);
}


void test_is_square_attacked_by_side_by_white(void)
{
    char *position = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K w kq - 0 1";
    Game *game = create_game_from_FEN(position);

    TEST_ASSERT_EQUAL_INT(0, is_square_attacked_by_side(game, E8, WHITE));
    TEST_ASSERT_EQUAL_INT(0, is_square_attacked_by_side(game, F7, WHITE));
    TEST_ASSERT_EQUAL_INT(0, is_square_attacked_by_side(game, C4, WHITE));
    TEST_ASSERT_EQUAL_INT(0, is_square_attacked_by_side(game, G7, WHITE));
    TEST_ASSERT_EQUAL_INT(0, is_square_attacked_by_side(game, D3, WHITE));
    TEST_ASSERT_EQUAL_INT(1, is_square_attacked_by_side(game, D5, WHITE));
    TEST_ASSERT_EQUAL_INT(1, is_square_attacked_by_side(game, H2, WHITE));
    TEST_ASSERT_EQUAL_INT(1, is_square_attacked_by_side(game, E2, WHITE));
    TEST_ASSERT_EQUAL_INT(1, is_square_attacked_by_side(game, F3, WHITE));

    free_game(game);
}

void test_is_square_attacked_by_side_by_black(void)
{
    char *position = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K w kq - 0 1";
    Game *game = create_game_from_FEN(position);

    TEST_ASSERT_EQUAL_INT(1, is_square_attacked_by_side(game, E8, BLACK));
    TEST_ASSERT_EQUAL_INT(1, is_square_attacked_by_side(game, F7, BLACK));
    TEST_ASSERT_EQUAL_INT(1, is_square_attacked_by_side(game, C4, BLACK));
    TEST_ASSERT_EQUAL_INT(0, is_square_attacked_by_side(game, G7, BLACK));
    TEST_ASSERT_EQUAL_INT(1, is_square_attacked_by_side(game, D3, BLACK));
    TEST_ASSERT_EQUAL_INT(1, is_square_attacked_by_side(game, D5, BLACK));
    TEST_ASSERT_EQUAL_INT(0, is_square_attacked_by_side(game, H2, BLACK));
    TEST_ASSERT_EQUAL_INT(0, is_square_attacked_by_side(game, E2, BLACK));
    TEST_ASSERT_EQUAL_INT(1, is_square_attacked_by_side(game, F3, BLACK));

    free_game(game);
}


// --- Cas de Test 1: Génération Complète (Base) ---

void test_generate_all_white_king_castling_moves_initial(void)
{
    // Objectif: Les deux roques blancs sont possibles (chemin libre, droits FEN 'KQ')
    char *position = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    generate_all_king_castling_moves_from_game_state(game, result);

    Move expected[] = {
        CREATE_MOVE(E1, G1, WHITE_KING, KING_CASTLE),
        CREATE_MOVE(E1, C1, WHITE_KING, QUEEN_CASTLE),
    };

    qsort(result->moves, result->current_index, sizeof(Move), compare_move);
    qsort(expected, 2, sizeof(Move), compare_move);

    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, result->moves, 2);
    TEST_ASSERT_EQUAL_INT(2, result->current_index);

    free_game(game);
    free(result);
}

void test_generate_all_black_king_castling_moves_initial(void)
{
    // Objectif: Les deux roques noirs sont possibles (chemin libre, droits FEN 'kq')
    char *position = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQkq - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    generate_all_king_castling_moves_from_game_state(game, result);

    Move expected[] = {
        CREATE_MOVE(E8, G8, BLACK_KING, KING_CASTLE),
        CREATE_MOVE(E8, C8, BLACK_KING, QUEEN_CASTLE),
    };

    qsort(result->moves, result->current_index, sizeof(Move), compare_move);
    qsort(expected, 2, sizeof(Move), compare_move);

    TEST_ASSERT_EQUAL_INT(2, result->current_index);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, result->moves, 2);

    free_game(game);
    free(result);
}

// --- Cas de Test 2: Blocage par Droits FEN (Doit ÊTRE vérifié) ---

void test_no_white_castling_due_to_fen_rights(void)
{
    // Objectif: Blanc ne peut roquer d'aucun côté (FEN '-'). Résultat: 0 mouvement.
    char *position = "r3k2r/8/8/8/8/8/8/R3K2R w - - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    generate_all_king_castling_moves_from_game_state(game, result);

    TEST_ASSERT_EQUAL_INT(0, result->current_index);

    free_game(game);
    free(result);
}

void test_only_black_queen_side_castling_due_to_fen_rights(void)
{
    // Objectif: Noir ne peut faire que le Grand roque (FEN 'q', manque 'k'). Résultat: 1 mouvement (Grand roque).
    char *position = "r3k2r/8/8/8/8/8/8/R3K2R b q - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    generate_all_king_castling_moves_from_game_state(game, result);

    Move expected[] = {
        CREATE_MOVE(E8, C8, BLACK_KING, QUEEN_CASTLE),
    };

    TEST_ASSERT_EQUAL_INT(1, result->current_index);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, result->moves, 1);

    free_game(game);
    free(result);
}

// --- Cas de Test 3: Blocage par Pièce Intermédiaire (Doit ÊTRE vérifié) ---

void test_no_white_king_side_castling_blocked_by_piece(void)
{
    // Objectif: Petit roque Blanc bloqué par un Fou en F1. Résultat: 1 mouvement (Grand roque).
    char *position = "r3k2r/8/8/8/8/8/8/R3KB1R w KQkq - 0 1"; 
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    generate_all_king_castling_moves_from_game_state(game, result);

    Move expected[] = {
        CREATE_MOVE(E1, C1, WHITE_KING, QUEEN_CASTLE),
    };

    qsort(result->moves, result->current_index, sizeof(Move), compare_move);
    qsort(expected, 1, sizeof(Move), compare_move);

    TEST_ASSERT_EQUAL_INT(1, result->current_index);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, result->moves, 1);

    free_game(game);
    free(result);
}

void test_no_white_queen_side_castling_blocked_by_piece(void)
{
    // Objectif: Grand roque Blanc bloqué par un Cavalier en C1 (et D1). Résultat: 1 mouvement (Petit roque).
    char *position = "r3k2r/8/8/8/8/8/8/R1NNK2R w KQkq - 0 1"; 
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    generate_all_king_castling_moves_from_game_state(game, result);

    Move expected[] = {
        CREATE_MOVE(E1, G1, WHITE_KING, KING_CASTLE),
    };

    qsort(result->moves, result->current_index, sizeof(Move), compare_move);
    qsort(expected, 1, sizeof(Move), compare_move);

    TEST_ASSERT_EQUAL_INT(1, result->current_index);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, result->moves, 1);

    free_game(game);
    free(result);
}

void test_no_black_king_side_castling_blocked_by_piece(void)
{
    // Objectif: Petit roque Noir bloqué par un Fou en F8. Résultat: 1 mouvement (Grand roque).
    char *position = "r3kb1r/8/8/8/8/8/8/R3K2R b KQkq - 0 1";
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    generate_all_king_castling_moves_from_game_state(game, result);

    Move expected[] = {
        CREATE_MOVE(E8, C8, BLACK_KING, QUEEN_CASTLE),
    };

    qsort(result->moves, result->current_index, sizeof(Move), compare_move);
    qsort(expected, 1, sizeof(Move), compare_move);

    TEST_ASSERT_EQUAL_INT(1, result->current_index);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, result->moves, 1);

    free_game(game);
    free(result);
}

// --- Cas de Test 4: Le Roi est en Échec (ne DOIT pas être généré) ---

void test_generate_white_castling_when_in_check_pseudo_legal(void)
{
    // Objectif: Les deux roques blancs ne DOIVENT pas être générés même si le Roi est en échec. Résultat: 0 mouvements.
    char *position = "r3k2r/8/8/8/8/8/4r3/R3K2R w KQkq - 0 1"; // Tour noire en E2 attaque E1
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    generate_all_king_castling_moves_from_game_state(game, result);

    TEST_ASSERT_EQUAL_INT(0, result->current_index);

    free_game(game);
    free(result);
}

// --- Cas de Test 5: Cases Traversées Attaquées (ne DOIT pas être généré) ---

void test_generate_white_castling_when_squares_attacked_pseudo_legal(void)
{
    // Objectif: Les deux roques blancs ne DOIVENT pas être générés même si les cases traversées/d'arrivée sont attaquées. Résultat: 0 mouvements.
    char *position = "5r2/8/8/7b/8/8/8/R3K2R w KQkq - 0 1"; 
    // F8 attaque F1; H5 attaque C1
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    generate_all_king_castling_moves_from_game_state(game, result);

    TEST_ASSERT_EQUAL_INT(0, result->current_index);

    free_game(game);
    free(result);
}

void test_generate_black_castling_when_squares_attacked_pseudo_legal(void)
{
    // Objectif: Seul le grand roque peut etre genere
    char *position = "r3k2r/8/8/2B5/8/8/8/R3K2R b KQkq - 0 1"; // Fou blanc en C5 attaque F8
    Game *game = create_game_from_FEN(position);

    MoveList* result = (MoveList*) malloc(sizeof(MoveList));
    result->current_index = 0;

    generate_all_king_castling_moves_from_game_state(game, result);

    Move expected[] = {
        CREATE_MOVE(E8, C8, BLACK_KING, QUEEN_CASTLE),
    };

    qsort(result->moves, result->current_index, sizeof(Move), compare_move);
    qsort(expected, 1, sizeof(Move), compare_move);

    TEST_ASSERT_EQUAL_INT(1, result->current_index);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, result->moves, 1);

    free_game(game);
    free(result);
}

void test_generate_all_white_king_capture_from_tricky_position(void)
{
    char *position_white = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K w kq - 0 1";
    
    Game *game_white = create_game_from_FEN(position_white);

    MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
    result_for_white->current_index = 0;

    Move expected_for_white[] = {
        CREATE_MOVE(H1, H2, WHITE_KING, CAPTURE),
    };
    
    generate_all_king_capture_moves_from_game_state(game_white, result_for_white);

    TEST_ASSERT_EQUAL(1, result_for_white->current_index);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_for_white, result_for_white->moves, 1);

    free_game(game_white);
    free(result_for_white);
}

void test_generate_all_black_king_capture_from_tricky_position(void)
{
    char *position_black = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1R1K b kq - 0 1";
    
    Game *game_black = create_game_from_FEN(position_black);

    MoveList* result_for_black = (MoveList*) malloc(sizeof(MoveList));
    result_for_black->current_index = 0;


    Move expected_for_black[] = {
        CREATE_MOVE(E8, F7, BLACK_KING, CAPTURE),
    };
    
    generate_all_king_capture_moves_from_game_state(game_black, result_for_black);
    
    TEST_ASSERT_EQUAL(1, result_for_black->current_index);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_for_black, result_for_black->moves, 1);
    free_game(game_black);

    free(result_for_black);
}

