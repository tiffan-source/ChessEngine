
#include "king_moves.h"

const Bitboard pre_calculated_king_moves[64] = {
    0x0000000000000302,
    0x0000000000000705,
    0x0000000000000e0a,
    0x0000000000001c14,
    0x0000000000003828,
    0x0000000000007050,
    0x000000000000e0a0,
    0x000000000000c040,
    0x0000000000030203,
    0x0000000000070507,
    0x00000000000e0a0e,
    0x00000000001c141c,
    0x0000000000382838,
    0x0000000000705070,
    0x0000000000e0a0e0,
    0x0000000000c040c0,
    0x0000000003020300,
    0x0000000007050700,
    0x000000000e0a0e00,
    0x000000001c141c00,
    0x0000000038283800,
    0x0000000070507000,
    0x00000000e0a0e000,
    0x00000000c040c000,
    0x0000000302030000,
    0x0000000705070000,
    0x0000000e0a0e0000,
    0x0000001c141c0000,
    0x0000003828380000,
    0x0000007050700000,
    0x000000e0a0e00000,
    0x000000c040c00000,
    0x0000030203000000,
    0x0000070507000000,
    0x00000e0a0e000000,
    0x00001c141c000000,
    0x0000382838000000,
    0x0000705070000000,
    0x0000e0a0e0000000,
    0x0000c040c0000000,
    0x0003020300000000,
    0x0007050700000000,
    0x000e0a0e00000000,
    0x001c141c00000000,
    0x0038283800000000,
    0x0070507000000000,
    0x00e0a0e000000000,
    0x00c040c000000000,
    0x0302030000000000,
    0x0705070000000000,
    0x0e0a0e0000000000,
    0x1c141c0000000000,
    0x3828380000000000,
    0x7050700000000000,
    0xe0a0e00000000000,
    0xc040c00000000000,
    0x0203000000000000,
    0x0507000000000000,
    0x0a0e000000000000,
    0x141c000000000000,
    0x2838000000000000,
    0x5070000000000000,
    0xa0e0000000000000,
    0x40c0000000000000
};

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

void generate_all_king_quiet_and_capture_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard white_king = board_state->white_king;
    Bitboard black_king = board_state->black_king;
    Bitboard move, attack;

    if(board_state->turn == WHITE)
    {
        while(white_king){
            source_square = get_lsb_index(white_king);

            move = pre_calculated_king_moves[source_square];
            while(move){
                target_square = get_lsb_index(move);

                if((1ULL << target_square) & (WHITE_OCCUPENCY(board_state))){
                    move = clear_bit_on_bitboard(move, target_square);
                    continue;
                } else {
                    moves_list->moves[moves_list->current_index++] = create_move(
                        source_square,
                        target_square,
                        WHITE_KING,
                        (1ULL << target_square) & (BLACK_OCCUPENCY(board_state)) ? CAPTURE : QUIET_MOVES
                    );
                }

                move = clear_bit_on_bitboard(move, target_square);
            }

            white_king = clear_bit_on_bitboard(white_king, source_square);
        }
    } else {
        while(black_king){
            source_square = get_lsb_index(black_king);

            move = pre_calculated_king_moves[source_square];
            while(move){
                target_square = get_lsb_index(move);

                if((1ULL << target_square) & (BLACK_OCCUPENCY(board_state))){
                    move = clear_bit_on_bitboard(move, target_square);
                    continue;
                } else {
                    moves_list->moves[moves_list->current_index++] = create_move(
                        source_square,
                        target_square,
                        BLACK_KING,
                        (1ULL << target_square) & (WHITE_OCCUPENCY(board_state)) ? CAPTURE : QUIET_MOVES    
                    );
                }

                move = clear_bit_on_bitboard(move, target_square);
            }

            black_king = clear_bit_on_bitboard(black_king, source_square);
        }
    }
}

int is_square_attacked(Game* board_state, Square square, Side side)
{
    //Attack by pawns
    Bitboard pawn_attacks = generate_pawns_capture_moves_from_square(side == WHITE ? BLACK : WHITE, square);
    Bitboard pawns = (side == WHITE) ? board_state->white_pawns : board_state->black_pawns;
    if(pawn_attacks & pawns)
        return 1;

    //Attack by knights
    Bitboard knight_attacks = generate_knights_moves_from_square(square);
    Bitboard knights = (side == WHITE) ? board_state->white_knights : board_state->black_knights;
    if(knight_attacks & knights)
        return 1;

    //Attack by bishops
    Bitboard bishop_attacks = retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
        square,
        ALL_OCCUPENCY(board_state)
    );
    Bitboard bishops = (side == WHITE) ? board_state->white_bishops : board_state->black_bishops;
    if(bishop_attacks & bishops)
        return 1;

    //Attack by rooks
    Bitboard rook_attacks = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
        square,
        ALL_OCCUPENCY(board_state)
    );
    Bitboard rooks = (side == WHITE) ? board_state->white_rooks : board_state->black_rooks;
    if(rook_attacks & rooks)
        return 1;

    //Attack by queens
    Bitboard queens = (side == WHITE) ? board_state->white_queens : board_state->black_queens;
    Bitboard queen_attacks = bishop_attacks | rook_attacks;
    if(queen_attacks & queens)
        return 1;

    //Attack by kings
    Bitboard king_attacks = pre_calculated_king_moves[square];
    Bitboard king = (side == WHITE) ? board_state->white_king : board_state->black_king;
    if(king_attacks & king)
        return 1;
    
    return 0;
}

void generate_all_king_castling_moves_from_game_state(Game* board_state, MoveList* moves_list)
{   
    Bitboard square_between_white_king_and_white_rook = 0x6000000000000000; // F1 and G1
    Bitboard square_between_white_king_and_white_queen_rook = 0x0E00000000000000; // D1, C1 and B1
    Bitboard square_between_black_king_and_black_rook = 0x0000000000000060; // F8 and G8
    Bitboard square_between_black_king_and_black_queen_rook = 0x000000000000000E; // D8, C8 and B8
    Bitboard occupency = ALL_OCCUPENCY(board_state);

    if (board_state->turn == WHITE_TURN)
    {
        if (board_state->castling_rights & WHITE_KING_SIDE_CASTLING)
        {
            if(!is_square_attacked(board_state, E1, BLACK) &&
               !is_square_attacked(board_state, F1, BLACK) )
            {
                if(!(occupency & square_between_white_king_and_white_rook))
                    moves_list->moves[moves_list->current_index++] = create_move(E1, G1, WHITE_KING, KING_CASTLE);
            }
        }
        if (board_state->castling_rights & WHITE_QUEEN_SIDE_CASTLING)
        {
            if (!is_square_attacked(board_state, E1, BLACK) &&
                !is_square_attacked(board_state, D1, BLACK) )
            {
                if(!(occupency & square_between_white_king_and_white_queen_rook))
                    moves_list->moves[moves_list->current_index++] = create_move(E1, C1, WHITE_KING, QUEEN_CASTLE);
            }
        }
    } else{
        if (board_state->castling_rights & BLACK_KING_SIDE_CASTLING)
        {
            if(!is_square_attacked(board_state, E8, WHITE) &&
               !is_square_attacked(board_state, F8, WHITE) )
            {
                if(!(occupency & square_between_black_king_and_black_rook))
                    moves_list->moves[moves_list->current_index++] = create_move(E8, G8, BLACK_KING, KING_CASTLE);
            }
        }
        if (board_state->castling_rights & BLACK_QUEEN_SIDE_CASTLING)
        {
            if (!is_square_attacked(board_state, E8, WHITE) &&
                !is_square_attacked(board_state, D8, WHITE) )
            {
                if(!(occupency & square_between_black_king_and_black_queen_rook))
                    moves_list->moves[moves_list->current_index++] = create_move(E8, C8, BLACK_KING, QUEEN_CASTLE);
            }
        }
    }
}

int is_king_attacked(Game* board_state, Side side)
{
    if (side == WHITE)
    {
        Square king_pos = get_lsb_index(board_state->black_king);
        return is_square_attacked(board_state, king_pos, side);
    }else{
        Square king_pos = get_lsb_index(board_state->white_king);
        return is_square_attacked(board_state, king_pos, side);
    }
}
