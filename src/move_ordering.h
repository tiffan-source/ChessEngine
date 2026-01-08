
#ifndef MOVE_ORDERING_H
#define MOVE_ORDERING_H

#include "moves.h"
#include "config.h"
#include "pv.h"

#define MAX_HISTORY 28000
#define clamp(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))


extern const int score_mvv_lva[6][6];
extern Move killer_move[MAX_DEPTH][2];
extern int history_heuristic[64][64];

void update_history_heuristic(ScoredMove* scored_move, int bonus);
void reset_history_heuristic();

void order_move(Game* game, MoveList* move, int ply, int follow_pv);
void add_killer_move_at_ply(Move move, int ply);
void reset_killer_moves();

#endif // MOVE_ORDERING_H
