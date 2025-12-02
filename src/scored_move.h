
#ifndef SCORED_MOVE_H
#define SCORED_MOVE_H

#include "moves.h"

typedef struct ScoredMove {
    long int score;
    Move move;
} ScoredMove;

#endif // SCORED_MOVE_H
