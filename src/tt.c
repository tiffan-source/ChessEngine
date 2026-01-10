
#include "tt.h"

TranspositionTable* tt = NULL;

void initialize_transposition_table()
{    
    /* Free any existing transposition table to avoid memory leaks on re-initialization */  
    if (tt != NULL) {  
        free_transposition_table();  
    }

    tt = malloc(sizeof(TranspositionTable));
    if(tt == NULL){
        fprintf(stderr, "Failed to allocate memory for Transposition Table\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < TRANSPOSITION_TABLE_SIZE; i++) {
        tt->entries[i].zobrist_key = 0;
        tt->entries[i].depth = -1;
        tt->entries[i].best_move.move = 0;
        tt->entries[i].best_move.score = 0;
        tt->entries[i].flag = TT_EMPTY;
    }
}

void free_transposition_table()
{
    if (tt != NULL) {
        free(tt);
        tt = NULL;
    }
}

TTEntry probe(U64 zobrist_key, int depth, int alpha, int beta)
{
    unsigned long long index = zobrist_key % TRANSPOSITION_TABLE_SIZE;
    TTEntry entry = tt->entries[index];

    if (entry.zobrist_key == zobrist_key) {
        if (entry.depth >= depth)
        {
            if(entry.best_move.score > (MAX - 100)) entry.best_move.score -= (get_depth() - depth);
            if(entry.best_move.score < -(MAX - 100)) entry.best_move.score += (get_depth() - depth);

            if (entry.flag == TT_EXACT) {
                return entry;
            } else if (entry.flag == TT_LOWERBOUND && entry.best_move.score >= beta) {
                return entry;
            } else if (entry.flag == TT_UPPERBOUND && entry.best_move.score <= alpha) {
                return entry;
            }
        }else{
            TTEntry depth_not_enough_entry = entry;
            depth_not_enough_entry.flag = TT_DEPTH_NOT_ENOUGH;
            return depth_not_enough_entry;
        }
    }

    TTEntry not_found_entry = {0};
    not_found_entry.flag = TT_NOT_FOUND;
    return not_found_entry;
}

void record(U64 zobrist_key, int depth, ScoredMove best_move, TTFlag flag)
{
    unsigned long long index = zobrist_key % TRANSPOSITION_TABLE_SIZE;

    if(best_move.score > (MAX - 100)) best_move.score += (get_depth() - depth);
    if(best_move.score < -(MAX - 100)) best_move.score -= (get_depth() - depth);

    tt->entries[index].zobrist_key = zobrist_key;
    tt->entries[index].depth = depth;
    tt->entries[index].best_move.score = best_move.score;
    tt->entries[index].best_move.move = best_move.move;
    tt->entries[index].flag = flag;
}
