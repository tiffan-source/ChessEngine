
#include "tt.h"

void initialize_transposition_table(TranspositionTable* tt)
{
    for (int i = 0; i < TRANSPOSITION_TABLE_SIZE; i++) {
        tt->entries[i].zobrist_key = 0;
        tt->entries[i].depth = -1;
        tt->entries[i].best_move.move = 0;
        tt->entries[i].best_move.score = 0;
        tt->entries[i].flag = TT_EMPTY;
    }
}

TTEntry probe(TranspositionTable* tt, U64 zobrist_key, int depth, int alpha, int beta)
{
    unsigned long long index = zobrist_key % TRANSPOSITION_TABLE_SIZE;
    TTEntry entry = tt->entries[index];

    if (entry.zobrist_key == zobrist_key && entry.depth >= depth) {

        if(entry.best_move.score > 900000) entry.best_move.score -= (get_depth() - depth);
        if(entry.best_move.score < -900000) entry.best_move.score += (get_depth() - depth);

        if (entry.flag == TT_EXACT) {
            return entry;
        } else if (entry.flag == TT_LOWERBOUND && entry.best_move.score >= beta) {
            return entry;
        } else if (entry.flag == TT_UPPERBOUND && entry.best_move.score <= alpha) {
            return entry;
        }
    }

    TTEntry not_found_entry = {0};
    not_found_entry.flag = TT_NOT_FOUND;
    return not_found_entry;
}

void record(TranspositionTable* tt, U64 zobrist_key, int depth, ScoredMove best_move, TTFlag flag)
{
    unsigned long long index = zobrist_key % TRANSPOSITION_TABLE_SIZE;

    if(best_move.score > 900000) best_move.score += (get_depth() - depth);
    if(best_move.score < -900000) best_move.score -= (get_depth() - depth);

    tt->entries[index].zobrist_key = zobrist_key;
    tt->entries[index].depth = depth;
    tt->entries[index].best_move.score = best_move.score;
    tt->entries[index].best_move.move = best_move.move;
    tt->entries[index].flag = flag;
}
