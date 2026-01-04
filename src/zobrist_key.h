
#ifndef TRANSPOSITION_TABLE_H
#define TRANSPOSITION_TABLE_H

#include "binary_tools.h"

typedef U64 ZobristKey;

extern ZobristKey pawn_zobrist_magic_number[2][64];
extern ZobristKey knight_zobrist_magic_number[2][64];
extern ZobristKey bishop_zobrist_magic_number[2][64];
extern ZobristKey rook_zobrist_magic_number[2][64];
extern ZobristKey queen_zobrist_magic_number[2][64];
extern ZobristKey king_zobrist_magic_number[2][64];

extern ZobristKey castling_rights_zobrist_magic_number[16];

extern ZobristKey black_to_move_zobrist_magic_number;

extern ZobristKey en_passant_square_zobrist_magic_number[64];

void initialize_magic_zobrist_numbers();


#endif // TRANSPOSITION_TABLE_H
