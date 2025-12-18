
#ifndef MOVE_ORDERING_H
#define MOVE_ORDERING_H

#include "moves.h"
#include "config.h"

extern const int score_mvv_lva[6][6];
extern Move killer_move[MAX_DEPTH][2];

void order_move(Game* game, MoveList* move, int ply);
void add_killer_move_at_ply(Move move, int ply);
void reset_killer_moves();

#endif // MOVE_ORDERING_H
