
#ifndef QUEENS_MOVES_H
#define QUEENS_MOVES_H

#include "game.h"
#include "moves.h"
#include "rooks_moves.h"
#include "bishops_moves.h"

void generate_all_white_queens_moves(Bitboard white_queens, Bitboard black_occupency, Bitboard all_occupency, MoveList* moves_list);
void generate_all_black_queens_moves(Bitboard black_queens, Bitboard white_occupency, Bitboard all_occupency, MoveList* moves_list);

void generate_all_white_queens_captures(Bitboard white_queens, Bitboard black_occupency, Bitboard all_occupency, MoveList* moves_list);
void generate_all_black_queens_captures(Bitboard black_queens, Bitboard white_occupency, Bitboard all_occupency, MoveList* moves_list);
#endif // QUEENS_MOVES_H
