
#ifndef EVALUATION_H
#define EVALUATION_H

#include "game.h"
#include "binary_tools.h"
#include "moves.h"
#include "king_moves.h"
#include "move_generator.h"
#include "standard_lib.h"

#define MIN -1000000
#define MAX 1000000

extern int pawn_square_table[64];

extern int knight_square_table[64];

extern int bishop_square_table[64];

extern int rook_square_table[64];

extern int king_square_table[64];

int material_evaluation_for_side(Game* game);
int material_evaluation_with_piece_square_table_for_side(Game* game);

#endif // EVALUATION_H
