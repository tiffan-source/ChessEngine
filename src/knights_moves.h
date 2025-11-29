
#ifndef KNIGHTS_MOVES_H
#define KNIGHTS_MOVES_H

#include "moves.h"
#include "game.h"

extern const Bitboard pre_calculated_knight_moves[64];

Bitboard generate_knights_moves_from_square(Square square);

void generate_all_knight_moves_from_game_state(Game* board_state, MoveList* moves_list);
#endif // KNIGHTS_MOVES_H
