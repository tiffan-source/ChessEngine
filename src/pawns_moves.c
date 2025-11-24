
#include "pawns_moves.h"


Bitboard generate_pawns_quiet_moves_from_square(Side side, Square square)
{
    Bitboard source = set_bit_on_bitboard(0x0ULL, square);
    Bitboard moves = 0x0ULL;

    if(side == WHITE)
    {
        // One square forward
        if(!bit_on_bitboard_hit_8_rank(source))
        {
            moves = set_bit_on_bitboard(moves, square - 8);

            // Two squares forward
            if(bit_on_bitboard_hit_2_rank(source))
            {
                moves = set_bit_on_bitboard(moves, square - 16);
            }
        }
    }
    else // BLACK
    {
        // One square forward
        if(!bit_on_bitboard_hit_1_rank(source))
        {
            moves = set_bit_on_bitboard(moves, square + 8);

            // Two squares forward from starting position
            if(bit_on_bitboard_hit_7_rank(source))
            {
                moves = set_bit_on_bitboard(moves, square + 16);
            }
        }
    }
    return moves;
}

Bitboard generate_pawns_capture_moves_from_square(Side side, Square square)
{
    Bitboard source = set_bit_on_bitboard(0x0ULL, square);
    Bitboard moves = 0x0ULL;

    if(side == WHITE && !bit_on_bitboard_hit_8_rank(source))
    {
        // Capture to the left
        if(!bit_on_bitboard_hit_a_file(source))
        {
            moves = set_bit_on_bitboard(moves, square - 9);
        }
        // Capture to the right
        if(!bit_on_bitboard_hit_h_file(source))
        {
            moves = set_bit_on_bitboard(moves, square - 7);
        }
    }
    else if(side == BLACK && !bit_on_bitboard_hit_1_rank(source)) // BLACK
    {
        // Capture to the left
        if(!bit_on_bitboard_hit_a_file(source))
        {
            moves = set_bit_on_bitboard(moves, square + 7);
        }
        // Capture to the right
        if(!bit_on_bitboard_hit_h_file(source))
        {
            moves = set_bit_on_bitboard(moves, square + 9);
        }
    }
    return moves;
}
