
#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "rooks_moves.h"
#include "knights_moves.h"
#include "bishops_moves.h"
#include "queens_moves.h"
#include "pawns_moves.h"
#include "king_moves.h"

void initialize_move_generation_databases();
void generate_all_pseudo_legal_moves_from_game_state(Game* game, MoveList* move_list);
void generate_all_pseudo_legal_capture_moves_from_game_state(Game* game, MoveList* move_list);

U64 generate_moves_from_position_at_depth(Game* game, int depth);
int get_time_ms();
U64 test_helper_generate_moves_from_position_at_depth(Game* game, int depth, int original_depth);

Move retrieve_uci_move_from_move_list(const char* uci_move_str, MoveList* move_list);
#endif // MOVE_GENERATOR_H
