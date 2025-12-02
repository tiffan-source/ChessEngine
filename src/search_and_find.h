
#ifndef SEARCH_AND_FIND_H
#define SEARCH_AND_FIND_H

#include "scored_move.h"
#include "evaluation.h"

// Function to find the best move using Min-Max algorithm with alpha-beta pruning
ScoredMove min_max_best_move_min(Game* game, int depth);
ScoredMove min_max_best_move_max(Game* game, int depth);



#endif // SEARCH_AND_FIND_H
