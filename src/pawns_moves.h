
#ifndef PAWNS_MOVES_H
#define PAWNS_MOVES_H

#include "game.h"
#include "moves.h"

extern Bitboard pre_calculated_pawn_push[2][64];
extern Bitboard pre_calculated_pawn_double_push[2][64];
extern Bitboard pre_calculated_pawn_attacks[2][64];

Bitboard generate_pawns_quiet_moves_one_square_from_square(Side side, Square square);
Bitboard generate_pawns_quiet_moves_two_squares_from_square(Side side, Square square);
Bitboard generate_pawns_capture_moves_from_square(Side side, Square square);

void generate_all_white_pawns_moves(Bitboard white_pawns, Bitboard black_occupency, Bitboard all_occupency, Square en_passant_square, MoveList* moves);
void generate_all_black_pawns_moves(Bitboard black_pawns, Bitboard white_occupency, Bitboard all_occupency, Square en_passant_square, MoveList* moves);

void initialize_pre_calculated_pawn_moves_database();
void initialize_pre_calculated_pawn_attacks_database();

void generate_all_white_pawns_capture_moves(Bitboard white_pawns, Bitboard black_occupency, Bitboard all_occupency, Square en_passant_square, MoveList* moves);
void generate_all_black_pawns_capture_moves(Bitboard black_pawns, Bitboard white_occupency, Bitboard all_occupency, Square en_passant_square, MoveList* moves);

#endif // PAWNS_MOVES_H
