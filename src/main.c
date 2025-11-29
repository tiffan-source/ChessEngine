#include "move_generator.h"

int main(int argc, char *argv[]) {

    int depth = 8;

    initialize_pre_calculated_bishop_moves_database();
    initialize_pre_calculated_pawn_attacks_database();
    initialize_pre_calculated_pawn_moves_database();
    initialize_pre_calculated_rook_moves_database();

    Game* game = create_game_from_FEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1 ");

    int start_time = get_time_ms();

    U64 result = test_helper_generate_moves_from_position_at_depth(game, depth, depth);

    printf("Total moves at depth %d: %llu\n", depth, result);
    printf("time taken to execute: %d ms\n", get_time_ms() - start_time);

    free_game(game);
}