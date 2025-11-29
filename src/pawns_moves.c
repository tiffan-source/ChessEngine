
#include "pawns_moves.h"

Bitboard pre_calculated_pawn_moves[2][64];
Bitboard pre_calculated_pawn_attacks[2][64];

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

void initialize_pre_calculated_pawn_moves_database()
{
    for (Square square = 0; square < 64; square++)
    {
        pre_calculated_pawn_moves[WHITE][square] = generate_pawns_quiet_moves_from_square(WHITE, square);
        pre_calculated_pawn_moves[BLACK][square] = generate_pawns_quiet_moves_from_square(BLACK, square);
    }
}

void initialize_pre_calculated_pawn_attacks_database()
{
    for (Square square = 0; square < 64; square++)
    {
        pre_calculated_pawn_attacks[WHITE][square] = generate_pawns_capture_moves_from_square(WHITE, square);
        pre_calculated_pawn_attacks[BLACK][square] = generate_pawns_capture_moves_from_square(BLACK, square);
    }
}

void generate_all_pawns_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard white_pawns;
    Bitboard black_pawns;
    Bitboard attack, move;
    Bitboard en_passant_bitboard;

    if (board_state->turn == WHITE_TURN)
    {        
        white_pawns = board_state->white_pawns;

        while(white_pawns){
            source_square = get_lsb_index(white_pawns);

            // Pawn moves
            move = pre_calculated_pawn_moves[WHITE][source_square];
            while(move){
                target_square = get_lsb_index(move);

                if((1ULL << target_square) & (BLACK_OCCUPENCY(board_state) | WHITE_OCCUPENCY(board_state))){
                    move = clear_bit_on_bitboard(move, target_square);
                    continue;
                } else {
                    if ((1ULL << target_square) & RANK_8)
                    {
                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            WHITE_PAWN, QUEEN_PROMOTION
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            WHITE_PAWN, ROOK_PROMOTION
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            WHITE_PAWN, BISHOP_PROMOTION
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            WHITE_PAWN, KNIGHT_PROMOTION
                        );
                    }else{
                        if (abs(source_square - target_square) == 16 && ((1ULL << (target_square + 8)) & (BLACK_OCCUPENCY(board_state) | WHITE_OCCUPENCY(board_state))) == 0 ){
                            moves_list->moves[moves_list->current_index++] = create_move(
                                source_square,
                                target_square,
                                WHITE_PAWN, DOUBLE_PAWN_PUSH
                            );
                        }else if (abs(source_square - target_square) != 16){
                            moves_list->moves[moves_list->current_index++] = create_move(
                                source_square,
                                target_square,
                                WHITE_PAWN, QUIET_MOVES
                            );
                        }
                    }
                }

                move = clear_bit_on_bitboard(move, target_square);
            }

            // Pawn attacks
            attack = pre_calculated_pawn_attacks[WHITE][source_square];
            while(attack){
                target_square = get_lsb_index(attack);

                if((1ULL << target_square) & BLACK_OCCUPENCY(board_state)){
                    if ((1ULL << target_square) & RANK_8){
                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            WHITE_PAWN, QUEEN_PROMOTION_CAPTURE
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            WHITE_PAWN, ROOK_PROMOTION_CAPTURE
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            WHITE_PAWN, BISHOP_PROMOTION_CAPTURE
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            WHITE_PAWN, KNIGHT_PROMOTION_CAPTURE
                        );
                    }else{
                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            WHITE_PAWN, CAPTURE);
                    }
                }

                attack = clear_bit_on_bitboard(attack, target_square);
            }

            white_pawns = clear_bit_on_bitboard(white_pawns, source_square);
        }

        // En Passant capture
        Square en_passant_square = (Square)(board_state->en_passant_target_square);
        if (en_passant_square != -1)
        {
            Bitboard source_attack = pre_calculated_pawn_attacks[BLACK][en_passant_square] & board_state->white_pawns;

            while (source_attack)
            {
                Square pawn_square = get_lsb_index(source_attack);
                moves_list->moves[moves_list->current_index++] = create_move(
                    pawn_square,
                    en_passant_square,
                    WHITE_PAWN,
                    EN_PASSANT_CAPTURE
                );
                source_attack = clear_bit_on_bitboard(source_attack, pawn_square);
            }
        }
    } else {
        black_pawns = board_state->black_pawns;

        while(black_pawns){
            source_square = get_lsb_index(black_pawns);

            // Pawn moves
            move = pre_calculated_pawn_moves[BLACK][source_square];
            while(move){
                target_square = get_lsb_index(move);

                if((1ULL << target_square) & (WHITE_OCCUPENCY(board_state) | BLACK_OCCUPENCY(board_state))){
                    move = clear_bit_on_bitboard(move, target_square);
                    continue;
                } else {
                    if ((1ULL << target_square) & RANK_1)
                    {
                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            BLACK_PAWN, QUEEN_PROMOTION
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            BLACK_PAWN, ROOK_PROMOTION
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            BLACK_PAWN, BISHOP_PROMOTION
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            BLACK_PAWN, KNIGHT_PROMOTION
                        );
                    }else{
                        if (
                            abs(source_square - target_square) == 16
                            &&
                            ((1ULL << (target_square - 8)) & (BLACK_OCCUPENCY(board_state) | WHITE_OCCUPENCY(board_state))) == 0
                        )
                        {
                            moves_list->moves[moves_list->current_index++] = create_move(
                                source_square,
                                target_square,
                                BLACK_PAWN, DOUBLE_PAWN_PUSH
                            );
                        }else if (abs(source_square - target_square) != 16){
                            moves_list->moves[moves_list->current_index++] = create_move(
                                source_square,
                                target_square,
                                BLACK_PAWN, QUIET_MOVES
                            );
                        }
                        
                    }
                    
                }

                move = clear_bit_on_bitboard(move, target_square);
            }

            // Pawn attacks
            attack = pre_calculated_pawn_attacks[BLACK][source_square];
            while(attack){
                target_square = get_lsb_index(attack);

                if((1ULL << target_square) & WHITE_OCCUPENCY(board_state)){
                    if ((1ULL << target_square) & RANK_1){
                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            BLACK_PAWN, QUEEN_PROMOTION_CAPTURE
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            BLACK_PAWN, ROOK_PROMOTION_CAPTURE
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            BLACK_PAWN, BISHOP_PROMOTION_CAPTURE
                        );

                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            BLACK_PAWN, KNIGHT_PROMOTION_CAPTURE
                        );
                    }else{
                        moves_list->moves[moves_list->current_index++] = create_move(
                            source_square,
                            target_square,
                            BLACK_PAWN, CAPTURE);
                    }
                }

                attack = clear_bit_on_bitboard(attack, target_square);
            }

            black_pawns = clear_bit_on_bitboard(black_pawns, source_square);
        }
    
    
        // En Passant capture
        Square en_passant_square = (Square)(board_state->en_passant_target_square);
        if (en_passant_square != -1)
        {
            Bitboard source_attack = pre_calculated_pawn_attacks[WHITE][en_passant_square] & board_state->black_pawns;

            while (source_attack)
            {
                Square pawn_square = get_lsb_index(source_attack);
                moves_list->moves[moves_list->current_index++] = create_move(
                    pawn_square,
                    en_passant_square,
                    BLACK_PAWN,
                    EN_PASSANT_CAPTURE
                );
                source_attack = clear_bit_on_bitboard(source_attack, pawn_square);
            }
        }
    }

    
}
