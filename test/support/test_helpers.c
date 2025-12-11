#include "test_helpers.h"
#include "unity.h"

int test_helper_compare_scored_move(const void *a, const void *b) {
    unsigned int ia = (*(const ScoredMove*)a).move;
    unsigned int ib = (*(const ScoredMove*)b).move;
    return (ia > ib) - (ia < ib);
}

void assert_move_lists_equal(ScoredMove* expected, ScoredMove* actual, int count) {
    for (int i = 0; i < count; i++) {
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[i].move, actual[i].move, "Move mismatch at index");
    }
}
