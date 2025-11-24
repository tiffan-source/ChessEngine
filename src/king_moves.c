
#include "king_moves.h"

Bitboard generate_king_moves_from_square(Square square)
{
    Bitboard source = set_bit_on_bitboard(0x0ULL, square);
    Bitboard moves = 0x0ULL;

    // Up
    if(!bit_on_bitboard_hit_8_rank(source))
        moves = set_bit_on_bitboard(moves, square - 8);
    // Down
    if(!bit_on_bitboard_hit_1_rank(source))
        moves = set_bit_on_bitboard(moves, square + 8);
    // Left
    if(!bit_on_bitboard_hit_a_file(source))
        moves = set_bit_on_bitboard(moves, square - 1);
    // Right
    if(!bit_on_bitboard_hit_h_file(source))
        moves = set_bit_on_bitboard(moves, square + 1);
    // Up-Left
    if(!bit_on_bitboard_hit_8_rank(source) && !bit_on_bitboard_hit_a_file(source))
        moves = set_bit_on_bitboard(moves, square - 9);
    // Up-Right
    if(!bit_on_bitboard_hit_8_rank(source) && !bit_on_bitboard_hit_h_file(source))
        moves = set_bit_on_bitboard(moves, square - 7);
    // Down-Left
    if(!bit_on_bitboard_hit_1_rank(source) && !bit_on_bitboard_hit_a_file(source))
        moves = set_bit_on_bitboard(moves, square + 7);
    // Down-Right
    if(!bit_on_bitboard_hit_1_rank(source) && !bit_on_bitboard_hit_h_file(source))
        moves = set_bit_on_bitboard(moves, square + 9);

    return moves;
}