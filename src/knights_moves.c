
#include "knights_moves.h"

Bitboard generate_knights_moves_from_square(Square square)
{
    Bitboard source = set_bit_on_bitboard(0x0ULL, square);
    Bitboard moves = 0x0ULL;

    // Up-Left-Left
    if(!bit_on_bitboard_hit_8_rank(source) && !bit_on_bitboard_hit_a_file(source) && !bit_on_bitboard_hit_b_file(source))
        moves = set_bit_on_bitboard(moves, square - 10);
    // Up-Up-Left
    if(!bit_on_bitboard_hit_8_rank(source) && !bit_on_bitboard_hit_7_rank(source) && !bit_on_bitboard_hit_a_file(source))
        moves = set_bit_on_bitboard(moves, square - 17);
    // Up-Up-Right
    if(!bit_on_bitboard_hit_8_rank(source) && !bit_on_bitboard_hit_7_rank(source) && !bit_on_bitboard_hit_h_file(source))
        moves = set_bit_on_bitboard(moves, square - 15);
    // Up-Right-Right
    if(!bit_on_bitboard_hit_8_rank(source) && !bit_on_bitboard_hit_g_file(source) && !bit_on_bitboard_hit_h_file(source))
        moves = set_bit_on_bitboard(moves, square - 6);
    // Down-Right-Right
    if(!bit_on_bitboard_hit_1_rank(source) && !bit_on_bitboard_hit_g_file(source) && !bit_on_bitboard_hit_h_file(source))
        moves = set_bit_on_bitboard(moves, square + 10);
    // Down-Down-Right
    if(!bit_on_bitboard_hit_1_rank(source) && !bit_on_bitboard_hit_2_rank(source) && !bit_on_bitboard_hit_h_file(source))
        moves = set_bit_on_bitboard(moves, square + 17);
    // Down-Down-Left
    if(!bit_on_bitboard_hit_1_rank(source) && !bit_on_bitboard_hit_2_rank(source) && !bit_on_bitboard_hit_a_file(source))
        moves = set_bit_on_bitboard(moves, square + 15);
    // Down-Left-Left
    if(!bit_on_bitboard_hit_1_rank(source) && !bit_on_bitboard_hit_a_file(source) && !bit_on_bitboard_hit_b_file(source))
        moves = set_bit_on_bitboard(moves, square + 6);
    return moves;
}