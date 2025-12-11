#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "moves.h"

/**
 * @brief Compare deux ScoredMove pour le tri (qsort).
 * Compare uniquement le champ 'move', ignore le score.
 */
int compare_scored_move(const void *a, const void *b);

/**
 * @brief Compare deux listes de ScoredMove en vérifiant uniquement le champ 'move'.
 * Utile pour les tests de génération de coups où le score n'est pas pertinent.
 * 
 * @param expected Liste attendue de ScoredMove
 * @param actual Liste générée de ScoredMove
 * @param count Nombre d'éléments à comparer
 */
void assert_move_lists_equal(ScoredMove* expected, ScoredMove* actual, int count);

#endif // TEST_HELPERS_H
