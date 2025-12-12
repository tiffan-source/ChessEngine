
#ifndef KNIGHTS_MOVES_H
#define KNIGHTS_MOVES_H

#include "moves.h"
#include "game.h"

extern const Bitboard pre_calculated_knight_moves[64];

Bitboard generate_knights_moves_from_square(Square square);

void generate_all_knight_moves_from_game_state(Game* board_state, MoveList* moves_list);
void generate_all_white_knight_moves_from_game_state(Game* board_state, MoveList* moves_list);
void generate_all_black_knight_moves_from_game_state(Game* board_state, MoveList* moves_list);

void generate_all_knight_captures_from_game_state(Game* board_state, MoveList* moves_list);
void generate_all_white_knight_captures_from_game_state(Game* board_state, MoveList* moves_list);
void generate_all_black_knight_captures_from_game_state(Game* board_state, MoveList* moves_list);
#endif // KNIGHTS_MOVES_H
