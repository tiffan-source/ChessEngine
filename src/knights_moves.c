
#include "knights_moves.h"

const Bitboard pre_calculated_knight_moves[64]= {
    0x0000000000020400,
    0x0000000000050800,
    0x00000000000a1100,
    0x0000000000142200,
    0x0000000000284400,
    0x0000000000508800,
    0x0000000000a01000,
    0x0000000000402000,
    0x0000000002040004,
    0x0000000005080008,
    0x000000000a110011,
    0x0000000014220022,
    0x0000000028440044,
    0x0000000050880088,
    0x00000000a0100010,
    0x0000000040200020,
    0x0000000204000402,
    0x0000000508000805,
    0x0000000a1100110a,
    0x0000001422002214,
    0x0000002844004428,
    0x0000005088008850,
    0x000000a0100010a0,
    0x0000004020002040,
    0x0000020400040200,
    0x0000050800080500,
    0x00000a1100110a00,
    0x0000142200221400,
    0x0000284400442800,
    0x0000508800885000,
    0x0000a0100010a000,
    0x0000402000204000,
    0x0002040004020000,
    0x0005080008050000,
    0x000a1100110a0000,
    0x0014220022140000,
    0x0028440044280000,
    0x0050880088500000,
    0x00a0100010a00000,
    0x0040200020400000,
    0x0204000402000000,
    0x0508000805000000,
    0x0a1100110a000000,
    0x1422002214000000,
    0x2844004428000000,
    0x5088008850000000,
    0xa0100010a0000000,
    0x4020002040000000,
    0x0400040200000000,
    0x0800080500000000,
    0x1100110a00000000,
    0x2200221400000000,
    0x4400442800000000,
    0x8800885000000000,
    0x100010a000000000,
    0x2000204000000000,
    0x0004020000000000,
    0x0008050000000000,
    0x00110a0000000000,
    0x0022140000000000,
    0x0044280000000000,
    0x0088500000000000,
    0x0010a00000000000,
    0x0020400000000000
};

Bitboard generate_knights_moves_from_square(Square square)
{
    Bitboard source = SET_BIT_ON_BITBOARD(0x0ULL, square);
    Bitboard moves = 0x0ULL;

    // Up-Left-Left
    if(!bit_on_bitboard_hit_8_rank(source) && !bit_on_bitboard_hit_a_file(source) && !bit_on_bitboard_hit_b_file(source))
        moves = SET_BIT_ON_BITBOARD(moves, square - 10);
    // Up-Up-Left
    if(!bit_on_bitboard_hit_8_rank(source) && !bit_on_bitboard_hit_7_rank(source) && !bit_on_bitboard_hit_a_file(source))
        moves = SET_BIT_ON_BITBOARD(moves, square - 17);
    // Up-Up-Right
    if(!bit_on_bitboard_hit_8_rank(source) && !bit_on_bitboard_hit_7_rank(source) && !bit_on_bitboard_hit_h_file(source))
        moves = SET_BIT_ON_BITBOARD(moves, square - 15);
    // Up-Right-Right
    if(!bit_on_bitboard_hit_8_rank(source) && !bit_on_bitboard_hit_g_file(source) && !bit_on_bitboard_hit_h_file(source))
        moves = SET_BIT_ON_BITBOARD(moves, square - 6);
    // Down-Right-Right
    if(!bit_on_bitboard_hit_1_rank(source) && !bit_on_bitboard_hit_g_file(source) && !bit_on_bitboard_hit_h_file(source))
        moves = SET_BIT_ON_BITBOARD(moves, square + 10);
    // Down-Down-Right
    if(!bit_on_bitboard_hit_1_rank(source) && !bit_on_bitboard_hit_2_rank(source) && !bit_on_bitboard_hit_h_file(source))
        moves = SET_BIT_ON_BITBOARD(moves, square + 17);
    // Down-Down-Left
    if(!bit_on_bitboard_hit_1_rank(source) && !bit_on_bitboard_hit_2_rank(source) && !bit_on_bitboard_hit_a_file(source))
        moves = SET_BIT_ON_BITBOARD(moves, square + 15);
    // Down-Left-Left
    if(!bit_on_bitboard_hit_1_rank(source) && !bit_on_bitboard_hit_a_file(source) && !bit_on_bitboard_hit_b_file(source))
        moves = SET_BIT_ON_BITBOARD(moves, square + 6);
    return moves;
}

void generate_all_knight_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Bitboard knights;
    Side side;
    Bitboard own_pieces;
    Bitboard opponent_pieces;
    Square from_square, to_square;
    Bitboard possible_moves;
    Bitboard temp_moves;
    
    if (board_state->turn == WHITE)
    {
        knights = board_state->white_knights;
        own_pieces = WHITE_OCCUPENCY(board_state);
        opponent_pieces = BLACK_OCCUPENCY(board_state);
        side = WHITE;
    }
    else
    {
        knights = board_state->black_knights;
        own_pieces = BLACK_OCCUPENCY(board_state);
        opponent_pieces = WHITE_OCCUPENCY(board_state);
        side = BLACK;
    }

    while (knights)
    {
        from_square = (Square)get_lsb_index(knights);
        possible_moves = generate_knights_moves_from_square(from_square);
        // Remove moves that land on own pieces
        possible_moves &= ~own_pieces;

        temp_moves = possible_moves;
        while (temp_moves)
        {
            to_square = (Square)get_lsb_index(temp_moves);
            if (opponent_pieces & (1ULL << to_square))
            {
                moves_list->moves[moves_list->current_index++] = create_move(from_square, to_square, (side == WHITE) ? WHITE_KNIGHT : BLACK_KNIGHT, CAPTURE);
            }
            else
            {
                moves_list->moves[moves_list->current_index++] = create_move(from_square, to_square, (side == WHITE) ? WHITE_KNIGHT : BLACK_KNIGHT, QUIET_MOVES);
            }
            temp_moves = clear_bit_on_bitboard(temp_moves, to_square);
        }

        knights = clear_bit_on_bitboard(knights, from_square);
    }
}