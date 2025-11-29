
#ifndef PAWNS_MOVES_H
#define PAWNS_MOVES_H

#include "game.h"
#include "moves.h"

extern Bitboard pre_calculated_pawn_moves[2][64];
extern Bitboard pre_calculated_pawn_attacks[2][64];

Bitboard generate_pawns_quiet_moves_from_square(Side side, Square square);
Bitboard generate_pawns_capture_moves_from_square(Side side, Square square);

void generate_all_pawns_moves_from_game_state(Game* board_state, MoveList* moves);

void initialize_pre_calculated_pawn_moves_database();
void initialize_pre_calculated_pawn_attacks_database();

#endif // PAWNS_MOVES_H
