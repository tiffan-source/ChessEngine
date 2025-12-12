
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
    Bitboard source = SET_BIT_ON_BITBOARD(0x0ULL, square);
    Bitboard moves = 0x0ULL;

    // Up
    if(!BIT_ON_BITBOARD_HIT_8_RANK(source))
        moves = SET_BIT_ON_BITBOARD(moves, square - 8);
    // Down
    if(!BIT_ON_BITBOARD_HIT_1_RANK(source))
        moves = SET_BIT_ON_BITBOARD(moves, square + 8);
    // Left
    if(!BIT_ON_BITBOARD_HIT_A_FILE(source))
        moves = SET_BIT_ON_BITBOARD(moves, square - 1);
    // Right
    if(!BIT_ON_BITBOARD_HIT_H_FILE(source))
        moves = SET_BIT_ON_BITBOARD(moves, square + 1);
    // Up-Left
    if(!BIT_ON_BITBOARD_HIT_8_RANK(source) && !BIT_ON_BITBOARD_HIT_A_FILE(source))
        moves = SET_BIT_ON_BITBOARD(moves, square - 9);
    // Up-Right
    if(!BIT_ON_BITBOARD_HIT_8_RANK(source) && !BIT_ON_BITBOARD_HIT_H_FILE(source))
        moves = SET_BIT_ON_BITBOARD(moves, square - 7);
    // Down-Left
    if(!BIT_ON_BITBOARD_HIT_1_RANK(source) && !BIT_ON_BITBOARD_HIT_A_FILE(source))
        moves = SET_BIT_ON_BITBOARD(moves, square + 7);
    // Down-Right
    if(!BIT_ON_BITBOARD_HIT_1_RANK(source) && !BIT_ON_BITBOARD_HIT_H_FILE(source))
        moves = SET_BIT_ON_BITBOARD(moves, square + 9);

    return moves;
}

void generate_all_king_quiet_and_capture_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    if(board_state->turn == WHITE)
    {
        generate_all_white_king_quiet_and_capture_moves_from_game_state(board_state, moves_list);
    } else {
        generate_all_black_king_quiet_and_capture_moves_from_game_state(board_state, moves_list);
    }
}

void generate_all_white_king_quiet_and_capture_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard white_king = board_state->white_king;
    Bitboard move, attack;
    Bitboard all_occupency = ALL_OCCUPENCY(board_state), black_occupency = BLACK_OCCUPENCY(board_state);

    while(white_king){
        source_square = GET_LSB_INDEX(white_king);

        move = pre_calculated_king_moves[source_square] & ~all_occupency;
        attack = pre_calculated_king_moves[source_square] & black_occupency;

        while(move){
            target_square = GET_LSB_INDEX(move);

            moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
                source_square,
                target_square,
                WHITE_KING,
                QUIET_MOVES
            );

            move = CLEAR_BIT_ON_BITBOARD(move, target_square);
        }

        while(attack){
            target_square = GET_LSB_INDEX(attack);

            moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
                source_square,
                target_square,
                WHITE_KING,
                CAPTURE
            );

            attack = CLEAR_BIT_ON_BITBOARD(attack, target_square);
        }

        white_king = CLEAR_BIT_ON_BITBOARD(white_king, source_square);
    }
}

void generate_all_black_king_quiet_and_capture_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard black_king = board_state->black_king;
    Bitboard move, attack;
    Bitboard all_occupency = ALL_OCCUPENCY(board_state), white_occupency = WHITE_OCCUPENCY(board_state);

    while(black_king){
        source_square = GET_LSB_INDEX(black_king);

        move = pre_calculated_king_moves[source_square] & ~all_occupency;
        attack = pre_calculated_king_moves[source_square] & white_occupency;

        while(move){
            target_square = GET_LSB_INDEX(move);

            moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
                source_square,
                target_square,
                BLACK_KING,
                QUIET_MOVES    
            );

            move = CLEAR_BIT_ON_BITBOARD(move, target_square);
        }

        while(attack){
            target_square = GET_LSB_INDEX(attack);

            moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
                source_square,
                target_square,
                BLACK_KING,
                CAPTURE
            );

            attack = CLEAR_BIT_ON_BITBOARD(attack, target_square);
        }

        black_king = CLEAR_BIT_ON_BITBOARD(black_king, source_square);
    }
}

int is_square_attacked_by_side(Game* board_state, Square square, Side side)
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
            if(!is_square_attacked_by_side(board_state, E1, BLACK) &&
               !is_square_attacked_by_side(board_state, F1, BLACK) )
            {
                if(!(occupency & square_between_white_king_and_white_rook))
                    moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(E1, G1, WHITE_KING, KING_CASTLE);
            }
        }
        if (board_state->castling_rights & WHITE_QUEEN_SIDE_CASTLING)
        {
            if (!is_square_attacked_by_side(board_state, E1, BLACK) &&
                !is_square_attacked_by_side(board_state, D1, BLACK) )
            {
                if(!(occupency & square_between_white_king_and_white_queen_rook))
                    moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(E1, C1, WHITE_KING, QUEEN_CASTLE);
            }
        }
    } else{
        if (board_state->castling_rights & BLACK_KING_SIDE_CASTLING)
        {
            if(!is_square_attacked_by_side(board_state, E8, WHITE) &&
               !is_square_attacked_by_side(board_state, F8, WHITE) )
            {
                if(!(occupency & square_between_black_king_and_black_rook))
                    moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(E8, G8, BLACK_KING, KING_CASTLE);
            }
        }
        if (board_state->castling_rights & BLACK_QUEEN_SIDE_CASTLING)
        {
            if (!is_square_attacked_by_side(board_state, E8, WHITE) &&
                !is_square_attacked_by_side(board_state, D8, WHITE) )
            {
                if(!(occupency & square_between_black_king_and_black_queen_rook))
                    moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(E8, C8, BLACK_KING, QUEEN_CASTLE);
            }
        }
    }
}

int is_king_attacked_by_side(Game* board_state, Side side)
{
    if (side == WHITE)
    {
        Square king_pos = GET_LSB_INDEX(board_state->black_king);
        return is_square_attacked_by_side(board_state, king_pos, side);
    }else{
        Square king_pos = GET_LSB_INDEX(board_state->white_king);
        return is_square_attacked_by_side(board_state, king_pos, side);
    }
}

void generate_all_king_capture_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    if(board_state->turn == WHITE)
    {
        generate_all_white_king_capture_moves_from_game_state(board_state, moves_list);
    } else {
        generate_all_black_king_capture_moves_from_game_state(board_state, moves_list);
    }
}

void generate_all_white_king_capture_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard white_king = board_state->white_king;
    Bitboard move;

    source_square = GET_LSB_INDEX(white_king);

    move = pre_calculated_king_moves[source_square] & BLACK_OCCUPENCY(board_state);
    while(move){
        target_square = GET_LSB_INDEX(move);
       
        moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
            source_square,
            target_square,
            WHITE_KING,
            CAPTURE
        );

        move = CLEAR_BIT_ON_BITBOARD(move, target_square);
    }
}

void generate_all_black_king_capture_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard black_king = board_state->black_king;
    Bitboard move;

    source_square = GET_LSB_INDEX(black_king);

    move = pre_calculated_king_moves[source_square] & WHITE_OCCUPENCY(board_state);
    while(move){
        target_square = GET_LSB_INDEX(move);

        moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
            source_square,
            target_square,
            BLACK_KING,
            CAPTURE
        );

        move = CLEAR_BIT_ON_BITBOARD(move, target_square);
    }
}