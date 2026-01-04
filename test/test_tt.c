

#include "unity.h"
#include "tt.h"
#include "moves.h"
#include "zobrist_key.h"
#include "binary_tools.h"
#include "board.h"
#include "pieces.h"
#include <stdlib.h>

TranspositionTable* tt;

void setUp(void)
{
    tt = malloc(sizeof(TranspositionTable));
    if (tt == NULL) {
        TEST_FAIL_MESSAGE("Failed to allocate memory for Transposition Table");
    }
    initialize_transposition_table(tt);
}

void tearDown(void)
{
    free(tt);
}

void test_initialize_transposition_table(void)
{
    // Check first, last and some middle entries
    int indices[] = {0, TRANSPOSITION_TABLE_SIZE - 1, TRANSPOSITION_TABLE_SIZE / 2};
    
    for (int i = 0; i < 3; i++) {
        int idx = indices[i];
        TEST_ASSERT_EQUAL_UINT64(0, tt->entries[idx].zobrist_key);
        TEST_ASSERT_EQUAL_INT(-1, tt->entries[idx].depth);
        TEST_ASSERT_EQUAL_UINT32(0, tt->entries[idx].best_move.move);
        TEST_ASSERT_EQUAL_INT(0, tt->entries[idx].best_move.score);
        TEST_ASSERT_EQUAL(TT_EMPTY, tt->entries[idx].flag);
    }
}

void test_record_and_probe_exact_match(void)
{
    U64 key = 0x123456789ABCDEF0;
    int depth = 5;
    ScoredMove sm = { .score = 100, .move = 12345 };
    
    record(tt, key, depth, sm, TT_EXACT);
    
    // Probe with exact match requirements
    // alpha and beta don't matter for TT_EXACT usually, but let's pass standard window
    TTEntry entry = probe(tt, key, depth, -1000, 1000);
    
    TEST_ASSERT_EQUAL_UINT64(key, entry.zobrist_key);
    TEST_ASSERT_EQUAL_INT(depth, entry.depth);
    TEST_ASSERT_EQUAL_INT(sm.score, entry.best_move.score);
    TEST_ASSERT_EQUAL_UINT32(sm.move, entry.best_move.move);
    TEST_ASSERT_EQUAL(TT_EXACT, entry.flag);
}

void test_probe_returns_not_found_if_empty(void)
{
    U64 key = 0xDEADBEEF;
    TTEntry entry = probe(tt, key, 1, -1000, 1000);
    
    TEST_ASSERT_EQUAL(TT_NOT_FOUND, entry.flag);
}

void test_probe_returns_not_found_if_depth_insufficient(void)
{
    U64 key = 0xCAFEBABE;
    int stored_depth = 4;
    int requested_depth = 5;
    ScoredMove sm = { .score = 50, .move = 111 };
    
    record(tt, key, stored_depth, sm, TT_EXACT);
    
    TTEntry entry = probe(tt, key, requested_depth, -1000, 1000);
    
    TEST_ASSERT_EQUAL(TT_NOT_FOUND, entry.flag);
}

void test_probe_returns_entry_if_depth_sufficient(void)
{
    U64 key = 0xCAFEBABE;
    int stored_depth = 5;
    int requested_depth = 4; // Requesting less depth than stored is fine
    ScoredMove sm = { .score = 50, .move = 111 };
    
    record(tt, key, stored_depth, sm, TT_EXACT);
    
    TTEntry entry = probe(tt, key, requested_depth, -1000, 1000);
    
    TEST_ASSERT_EQUAL(TT_EXACT, entry.flag);
    TEST_ASSERT_EQUAL_UINT64(key, entry.zobrist_key);
}

void test_probe_lowerbound_cutoff(void)
{
    U64 key = 0x1122334455667788;
    int depth = 5;
    int score = 100;
    ScoredMove sm = { .score = score, .move = 123 };
    
    record(tt, key, depth, sm, TT_LOWERBOUND);
    
    // Case 1: score >= beta -> Cutoff (Return entry)
    int beta = 90;
    TTEntry entry = probe(tt, key, depth, -1000, beta);
    TEST_ASSERT_EQUAL(TT_LOWERBOUND, entry.flag);
    TEST_ASSERT_EQUAL_INT(score, entry.best_move.score);
    
    // Case 2: score < beta -> No Cutoff (Return NOT_FOUND)
    beta = 110;
    entry = probe(tt, key, depth, -1000, beta);
    TEST_ASSERT_EQUAL(TT_NOT_FOUND, entry.flag);
}

void test_probe_upperbound_cutoff(void)
{
    U64 key = 0x8877665544332211;
    int depth = 5;
    int score = 100;
    ScoredMove sm = { .score = score, .move = 123 };
    
    record(tt, key, depth, sm, TT_UPPERBOUND);
    
    // Case 1: score <= alpha -> Cutoff (Return entry)
    int alpha = 110;
    TTEntry entry = probe(tt, key, depth, alpha, 2000);
    TEST_ASSERT_EQUAL(TT_UPPERBOUND, entry.flag);
    TEST_ASSERT_EQUAL_INT(score, entry.best_move.score);
    
    // Case 2: score > alpha -> No Cutoff (Return NOT_FOUND)
    alpha = 90;
    entry = probe(tt, key, depth, alpha, 2000);
    TEST_ASSERT_EQUAL(TT_NOT_FOUND, entry.flag);
}

void test_record_overwrites_existing_entry(void)
{
    U64 key = 0xAAAA5555AAAA5555;
    int depth1 = 3;
    ScoredMove sm1 = { .score = 10, .move = 1 };
    
    record(tt, key, depth1, sm1, TT_EXACT);
    
    // Verify first record
    TTEntry entry = probe(tt, key, depth1, -1000, 1000);
    TEST_ASSERT_EQUAL_INT(10, entry.best_move.score);
    
    // Overwrite with new data (same key, different values)
    int depth2 = 6;
    ScoredMove sm2 = { .score = 20, .move = 2 };
    record(tt, key, depth2, sm2, TT_EXACT);
    
    // Verify overwrite
    entry = probe(tt, key, depth2, -1000, 1000);
    TEST_ASSERT_EQUAL_INT(20, entry.best_move.score);
    TEST_ASSERT_EQUAL_INT(depth2, entry.depth);
}

void test_collision_handling(void)
{
    // We need two keys that map to the same index.
    // Index = key % TRANSPOSITION_TABLE_SIZE
    // TRANSPOSITION_TABLE_SIZE is 1048576 (2^20)
    
    U64 key1 = 1;
    U64 key2 = 1 + TRANSPOSITION_TABLE_SIZE; // Should map to same index 1
    
    ScoredMove sm1 = { .score = 10, .move = 1 };
    record(tt, key1, 5, sm1, TT_EXACT);
    
    // Verify key1 is there
    TTEntry entry = probe(tt, key1, 5, -1000, 1000);
    TEST_ASSERT_EQUAL_UINT64(key1, entry.zobrist_key);
    
    // Record key2, should overwrite key1 because implementation is simple always-replace
    ScoredMove sm2 = { .score = 20, .move = 2 };
    record(tt, key2, 5, sm2, TT_EXACT);
    
    // Verify key2 is there
    entry = probe(tt, key2, 5, -1000, 1000);
    TEST_ASSERT_EQUAL_UINT64(key2, entry.zobrist_key);
    
    // Verify key1 is NOT found (it was overwritten)
    entry = probe(tt, key1, 5, -1000, 1000);
    TEST_ASSERT_EQUAL(TT_NOT_FOUND, entry.flag);
}
