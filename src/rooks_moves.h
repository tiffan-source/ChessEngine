
#ifndef ROOKS_MOVES_H
#define ROOKS_MOVES_H

#include "board.h"
#include "time.h"

extern const int number_of_bit_in_rook_mask_for_square[64];
extern const Bitboard rook_magic_numbers[64];
extern const Bitboard pre_calculated_rook_masks[64];
extern Bitboard pre_calculated_rook_moves_database[64][4096];

Bitboard generate_rook_moves_from_square_without_blocking_piece(Square square);
Bitboard generate_rook_moves_from_square_without_blocking_piece_edge_remove(Square square);
Bitboard get_rook_blocker_configuration_for_square_giving_index(Square square, int index);

int test_candidate_magic_bitboard_rook(Square square, Bitboard magic_number);
Bitboard generate_magic_number_for_rook_on_square(Square square);
Bitboard* generate_all_magic_numbers_for_rooks();

Bitboard generate_rook_moves_for_giving_blocker_configuration(Square square, Bitboard blocker);

void initialize_pre_calculated_rook_moves_database();

Bitboard retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(Square square, Bitboard blocker);
#endif // ROOKS_MOVES_H
