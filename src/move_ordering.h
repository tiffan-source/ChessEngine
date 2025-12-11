
#ifndef MOVE_ORDERING_H
#define MOVE_ORDERING_H

#include "moves.h"

extern const int score_mvv_lva[6][6];

void order_move_using_mvv_lva(Game* game, MoveList* move);

#endif // MOVE_ORDERING_H
