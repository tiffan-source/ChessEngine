
// #ifdef TEST

#include "unity.h"

#include "queens_moves.h"
#include "rooks_moves.h"
#include "bishops_moves.h"
#include "board.h"
#include "binary_tools.h"
#include "game.h"
#include "moves.h"
#include "pieces.h"

void setUp(void)
{
    initialize_pre_calculated_rook_moves_database();
    initialize_pre_calculated_bishop_moves_database();
}

void tearDown(void)
{
}

static int compare_move(const void *a, const void *b) {
    int ia = *(const Move*)a;
    int ib = *(const Move*)b;
    return ia - ib;
}

// void test_generate_all_white_queens_move_from_tricky_position(void)
// {
//     char *position_white = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K w kq - 0 1";
    
//     Game *game_white = create_game_from_FEN(position_white);

//     MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
//     result_for_white->current_index = 0;

//     Move expected_for_white[] = {
//         CREATE_MOVE(D1, C2, WHITE_QUEEN, QUIET_MOVES),
//         CREATE_MOVE(D1, B3, WHITE_QUEEN, QUIET_MOVES),
//         CREATE_MOVE(D1, C1, WHITE_QUEEN, QUIET_MOVES),
//         CREATE_MOVE(D1, B1, WHITE_QUEEN, QUIET_MOVES),
//         CREATE_MOVE(D1, E1, WHITE_QUEEN, QUIET_MOVES),
//         CREATE_MOVE(D1, E2, WHITE_QUEEN, QUIET_MOVES),
//     };
    
//     generate_all_queens_moves_from_game_state(game_white, result_for_white);

//     qsort(result_for_white->moves, result_for_white->current_index, sizeof(Move), compare_move);
//     qsort(expected_for_white, 6, sizeof(Move), compare_move);    

//     TEST_ASSERT_EQUAL_INT(6, result_for_white->current_index);
//     TEST_ASSERT_EQUAL_UINT_ARRAY(expected_for_white, result_for_white->moves, 6);

//     free_game(game_white);
//     free(result_for_white);
// }

void test_generate_all_white_queens_move_from_Kiwipete_position(void)
{
    char *position_white = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -";
    
    Game *game_white = create_game_from_FEN(position_white);

    MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
    result_for_white->current_index = 0;

    Move expected_for_white[] = {
        CREATE_MOVE(F3, F4, WHITE_QUEEN, QUIET_MOVES),
        CREATE_MOVE(F3, F5, WHITE_QUEEN, QUIET_MOVES),
        CREATE_MOVE(F3, F6, WHITE_QUEEN, CAPTURE),

        CREATE_MOVE(F3, E3, WHITE_QUEEN, QUIET_MOVES),
        CREATE_MOVE(F3, D3, WHITE_QUEEN, QUIET_MOVES),

        CREATE_MOVE(F3, G3, WHITE_QUEEN, QUIET_MOVES),
        CREATE_MOVE(F3, H3, WHITE_QUEEN, CAPTURE),

        CREATE_MOVE(F3, G4, WHITE_QUEEN, QUIET_MOVES),
        CREATE_MOVE(F3, H5, WHITE_QUEEN, QUIET_MOVES),
    };
    
    generate_all_queens_moves_from_game_state(game_white, result_for_white);

    qsort(result_for_white->moves, result_for_white->current_index, sizeof(Move), compare_move);
    qsort(expected_for_white, 9, sizeof(Move), compare_move);    

    TEST_ASSERT_EQUAL_INT(9, result_for_white->current_index);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_for_white, result_for_white->moves, 9);

    free_game(game_white);
    free(result_for_white);
}

// void test_generate_all_black_queens_move_from_tricky_position(void)
// {
//     char *position_black = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K b kq - 0 1";

//     Game *game_black = create_game_from_FEN(position_black);

//     MoveList* result_for_black = (MoveList*) malloc(sizeof(MoveList));
//     result_for_black->current_index = 0;

//     Move expected_for_black[] = {
//         CREATE_MOVE(A3, A4, BLACK_QUEEN, CAPTURE),
//         CREATE_MOVE(A3, B4, BLACK_QUEEN, CAPTURE),
//         CREATE_MOVE(A3, B3, BLACK_QUEEN, QUIET_MOVES),
//         CREATE_MOVE(A3, C3, BLACK_QUEEN, QUIET_MOVES),
//         CREATE_MOVE(A3, D3, BLACK_QUEEN, QUIET_MOVES),
//         CREATE_MOVE(A3, E3, BLACK_QUEEN, QUIET_MOVES),
//         CREATE_MOVE(A3, F3, BLACK_QUEEN, CAPTURE),
//         CREATE_MOVE(A3, A2, BLACK_QUEEN, CAPTURE),
//     };
    
//     generate_all_queens_moves_from_game_state(game_black, result_for_black);
    
//     qsort(result_for_black->moves, result_for_black->current_index, sizeof(Move), compare_move);
//     qsort(expected_for_black, 8, sizeof(Move), compare_move);

//     TEST_ASSERT_EQUAL_INT(8, result_for_black->current_index);
//     TEST_ASSERT_EQUAL_UINT_ARRAY(expected_for_black, result_for_black->moves, 8);
//     free_game(game_black);

//     free(result_for_black);
// }

// void test_generate_all_black_queens_capture_from_tricky_position(void)
// {
//     char *position_black = "r3k2r/Pppp1Npp/1b3nb1/nP6/BBP1P3/q4N2/Pp1P2Pp/R2Q1R1K b kq - 0 1";

//     Game *game_black = create_game_from_FEN(position_black);

//     MoveList* result_for_black = (MoveList*) malloc(sizeof(MoveList));
//     result_for_black->current_index = 0;

//     Move expected_for_black[] = {
//         CREATE_MOVE(A3, A4, BLACK_QUEEN, CAPTURE),
//         CREATE_MOVE(A3, B4, BLACK_QUEEN, CAPTURE),
//         CREATE_MOVE(A3, F3, BLACK_QUEEN, CAPTURE),
//         CREATE_MOVE(A3, A2, BLACK_QUEEN, CAPTURE),
//     };
    
//     generate_all_queens_captures_from_game_state(game_black, result_for_black);
    
//     qsort(result_for_black->moves, result_for_black->current_index, sizeof(Move), compare_move);
//     qsort(expected_for_black, 4, sizeof(Move), compare_move);

//     TEST_ASSERT_EQUAL(4, result_for_black->current_index);
//     TEST_ASSERT_EQUAL_UINT_ARRAY(expected_for_black, result_for_black->moves, 4);
//     free_game(game_black);

//     free(result_for_black);
// }

// void test_generate_all_white_queens_mcapture_from_tricky_position(void)
// {
//     char *position_white = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";

//     Game *game_white = create_game_from_FEN(position_white);

//     MoveList* result_for_white = (MoveList*) malloc(sizeof(MoveList));
//     result_for_white->current_index = 0;

//     Move expected_for_black[] = {
//         CREATE_MOVE(F3, H3, WHITE_QUEEN, CAPTURE),
//         CREATE_MOVE(F3, F6, WHITE_QUEEN, CAPTURE)
//     };
    
//     generate_all_queens_captures_from_game_state(game_white, result_for_white);
    
//     qsort(result_for_white->moves, result_for_white->current_index, sizeof(Move), compare_move);
//     qsort(expected_for_black, 2, sizeof(Move), compare_move);

//     TEST_ASSERT_EQUAL(2, result_for_white->current_index);
//     TEST_ASSERT_EQUAL_UINT_ARRAY(expected_for_black, result_for_white->moves, 2);
//     free_game(game_white);

//     free(result_for_white);
// }

// #endif // TEST
