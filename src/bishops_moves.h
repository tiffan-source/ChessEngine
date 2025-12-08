
#ifndef BISHOPS_MOVES_H
#define BISHOPS_MOVES_H

#include "moves.h"
#include "game.h"


extern const int number_of_bit_in_bishop_mask_for_square[64];
extern const Bitboard bishop_magic_numbers[64];
extern const Bitboard pre_calculated_bishop_masks[64];
extern Bitboard pre_calculated_bishop_moves_database[64][512];

Bitboard generate_bishop_moves_from_square_without_blocking_piece(Square square);
Bitboard generate_bishop_moves_from_square_without_blocking_piece_edge_remove(Square square);
Bitboard get_bishop_blocker_configuration_for_square_giving_index(Square square, int index);

int test_candidate_magic_bitboard_bishop(Square square, Bitboard magic_number);
Bitboard generate_magic_number_for_bishop_on_square(Square square);
Bitboard* generate_all_magic_numbers_for_bishops();

/**
 * @brief Generate bishop moves for a given square and blocker configuration.
 * 
 * @param square The square where the bishop is located.
 * @param blocker The bitboard representing the blocker configuration.
 * @return Bitboard The bitboard representing the possible moves for the bishop.
 */
Bitboard generate_bishop_moves_for_giving_blocker_configuration(Square square, Bitboard blocker);

void initialize_pre_calculated_bishop_moves_database();

/**
 * @brief Retrieve pre-calculated bishop moves for a given square and blocker configuration.
 * 
 * @param square The square where the bishop is located.
 * @param blocker The bitboard representing the blocker configuration.
 * @return Bitboard The bitboard representing the possible moves for the bishop.
 */
Bitboard retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(Square square, Bitboard blocker);

void generate_all_bishop_moves_from_game_state(Game* board_state, MoveList* moves_list);
void generate_all_bishop_captures_from_game_state(Game* board_state, MoveList* moves_list);

#endif // BISHOPS_MOVES_H
