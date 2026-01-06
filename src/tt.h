
#ifndef TT_H
#define TT_H

#include "zobrist_key.h"
#include "moves.h"
#include "evaluation.h"
#include "config.h"

#define TRANSPOSITION_TABLE_SIZE 1048576 // 2^20 entries

typedef enum {
    TT_EMPTY,
    TT_EXACT,
    TT_LOWERBOUND,
    TT_UPPERBOUND,
    TT_NOT_FOUND
} TTFlag;

typedef struct TranspositionTableEntry {
    U64 zobrist_key;
    int depth;
    ScoredMove best_move;
    TTFlag flag;
} TTEntry;

typedef struct TranspositionTable {
    TTEntry entries[TRANSPOSITION_TABLE_SIZE];
} TranspositionTable;

void initialize_transposition_table(TranspositionTable* tt);

TTEntry probe(TranspositionTable* tt, U64 zobrist_key, int depth, int alpha, int beta);
void record(TranspositionTable* tt, U64 zobrist_key, int depth, ScoredMove best_move, TTFlag flag);

#endif // TT_H