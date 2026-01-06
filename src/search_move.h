
#ifndef SEARCH_AND_FIND_H
#define SEARCH_AND_FIND_H

#include "evaluation.h"
#include "config.h"
#include "move_ordering.h"
#include "tt.h"
#include "pv.h"

#define MIN -1000000
#define MAX 1000000

U64 get_nodes_searched();

ScoredMove call_search_algorithm(Game* game, int depth);

ScoredMove nega_alpha_beta(Game *game, int depth, int alpha, int beta, TranspositionTable* tt);

#endif // SEARCH_AND_FIND_H
