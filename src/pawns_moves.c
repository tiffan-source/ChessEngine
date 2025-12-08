
#include "pawns_moves.h"

Bitboard pre_calculated_pawn_moves[2][64];
Bitboard pre_calculated_pawn_attacks[2][64];

Bitboard generate_pawns_quiet_moves_from_square(Side side, Square square)
{
    Bitboard source = SET_BIT_ON_BITBOARD(0x0ULL, square);
    Bitboard moves = 0x0ULL;

    if(side == WHITE)
    {
        // One square forward
        if(!BIT_ON_BITBOARD_HIT_8_RANK(source))
        {
            moves = SET_BIT_ON_BITBOARD(moves, square - 8);

            // Two squares forward
            if(BIT_ON_BITBOARD_HIT_2_RANK(source))
            {
                moves = SET_BIT_ON_BITBOARD(moves, square - 16);
            }
        }
    }
    else // BLACK
    {
        // One square forward
        if(!BIT_ON_BITBOARD_HIT_1_RANK(source))
        {
            moves = SET_BIT_ON_BITBOARD(moves, square + 8);

            // Two squares forward from starting position
            if(BIT_ON_BITBOARD_HIT_7_RANK(source))
            {
                moves = SET_BIT_ON_BITBOARD(moves, square + 16);
            }
        }
    }
    return moves;
}

Bitboard generate_pawns_capture_moves_from_square(Side side, Square square)
{
    Bitboard source = SET_BIT_ON_BITBOARD(0x0ULL, square);
    Bitboard moves = 0x0ULL;

    if(side == WHITE && !BIT_ON_BITBOARD_HIT_8_RANK(source))
    {
        // Capture to the left
        if(!BIT_ON_BITBOARD_HIT_A_FILE(source))
        {
            moves = SET_BIT_ON_BITBOARD(moves, square - 9);
        }
        // Capture to the right
        if(!BIT_ON_BITBOARD_HIT_H_FILE(source))
        {
            moves = SET_BIT_ON_BITBOARD(moves, square - 7);
        }
    }
    else if(side == BLACK && !BIT_ON_BITBOARD_HIT_1_RANK(source)) // BLACK
    {
        // Capture to the left
        if(!BIT_ON_BITBOARD_HIT_A_FILE(source))
        {
            moves = SET_BIT_ON_BITBOARD(moves, square + 7);
        }
        // Capture to the right
        if(!BIT_ON_BITBOARD_HIT_H_FILE(source))
        {
            moves = SET_BIT_ON_BITBOARD(moves, square + 9);
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
    Bitboard black_occupency = BLACK_OCCUPENCY(board_state);
    Bitboard white_occupency = WHITE_OCCUPENCY(board_state);
    Bitboard all_occupency = black_occupency | white_occupency;
    int diff_source_tag;

    if (board_state->turn == WHITE_TURN)
    {        
        white_pawns = board_state->white_pawns;

        while(white_pawns){
            source_square = GET_LSB_INDEX(white_pawns);

            // Pawn moves
            move = pre_calculated_pawn_moves[WHITE][source_square] & ~all_occupency;
            while(move){
                target_square = GET_LSB_INDEX(move);

                // if((pre_calculated_bit_shifts[target_square]) & all_occupency){
                //     move = CLEAR_BIT_ON_BITBOARD(move, target_square);
                //     continue;
                // } else {
                    if ((pre_calculated_bit_shifts[target_square]) & RANK_8)
                    {
                        moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                            source_square,
                            target_square,
                            WHITE_PAWN, QUEEN_PROMOTION
                        );

                        moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                            source_square,
                            target_square,
                            WHITE_PAWN, ROOK_PROMOTION
                        );

                        moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                            source_square,
                            target_square,
                            WHITE_PAWN, BISHOP_PROMOTION
                        );

                        moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                            source_square,
                            target_square,
                            WHITE_PAWN, KNIGHT_PROMOTION
                        );
                    }
                    else
                    {
                        diff_source_tag = abs(source_square - target_square);
                        if (diff_source_tag == 16 && ((pre_calculated_bit_shifts[target_square + 8]) & all_occupency) == 0 ){
                            moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                                source_square,
                                target_square,
                                WHITE_PAWN, DOUBLE_PAWN_PUSH
                            );
                        }else if (diff_source_tag != 16){
                            moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                                source_square,
                                target_square,
                                WHITE_PAWN, QUIET_MOVES
                            );
                        }
                    }
                // }

                move = CLEAR_BIT_ON_BITBOARD(move, target_square);
            }

            // Pawn attacks
            attack = pre_calculated_pawn_attacks[WHITE][source_square] & black_occupency;
            while(attack){
                target_square = GET_LSB_INDEX(attack);

                if ((pre_calculated_bit_shifts[target_square]) & RANK_8){
                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        WHITE_PAWN, QUEEN_PROMOTION_CAPTURE
                    );

                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        WHITE_PAWN, ROOK_PROMOTION_CAPTURE
                    );

                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        WHITE_PAWN, BISHOP_PROMOTION_CAPTURE
                    );

                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        WHITE_PAWN, KNIGHT_PROMOTION_CAPTURE
                    );
                }else{
                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        WHITE_PAWN, CAPTURE);
                }

                attack = CLEAR_BIT_ON_BITBOARD(attack, target_square);
            }

            white_pawns = CLEAR_BIT_ON_BITBOARD(white_pawns, source_square);
        }

        // En Passant capture
        Square en_passant_square = (Square)(board_state->en_passant_target_square);
        if (en_passant_square != -1)
        {
            Bitboard source_attack = pre_calculated_pawn_attacks[BLACK][en_passant_square] & board_state->white_pawns;

            while (source_attack)
            {
                Square pawn_square = GET_LSB_INDEX(source_attack);
                moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                    pawn_square,
                    en_passant_square,
                    WHITE_PAWN,
                    EN_PASSANT_CAPTURE
                );
                source_attack = CLEAR_BIT_ON_BITBOARD(source_attack, pawn_square);
            }
        }
    } else {
        black_pawns = board_state->black_pawns;

        while(black_pawns){
            source_square = GET_LSB_INDEX(black_pawns);

            // Pawn moves
            move = pre_calculated_pawn_moves[BLACK][source_square]  &  ~all_occupency;
            while(move){
                target_square = GET_LSB_INDEX(move);

                if ((pre_calculated_bit_shifts[target_square]) & RANK_1)
                {
                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_PAWN, QUEEN_PROMOTION
                    );

                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_PAWN, ROOK_PROMOTION
                    );

                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_PAWN, BISHOP_PROMOTION
                    );

                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_PAWN, KNIGHT_PROMOTION
                    );
                }else{
                    diff_source_tag = abs(source_square - target_square);
                    if (
                        diff_source_tag == 16
                        &&
                        ((pre_calculated_bit_shifts[target_square - 8]) & all_occupency) == 0
                    )
                    {
                        moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                            source_square,
                            target_square,
                            BLACK_PAWN, DOUBLE_PAWN_PUSH
                        );
                    }else if (diff_source_tag != 16){
                        moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                            source_square,
                            target_square,
                            BLACK_PAWN, QUIET_MOVES
                        );
                    }
                    
                }
                    
                move = CLEAR_BIT_ON_BITBOARD(move, target_square);
            }

            // Pawn attacks
            attack = pre_calculated_pawn_attacks[BLACK][source_square] & white_occupency;
            while(attack){
                target_square = GET_LSB_INDEX(attack);

                if ((pre_calculated_bit_shifts[target_square]) & RANK_1){
                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_PAWN, QUEEN_PROMOTION_CAPTURE
                    );

                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_PAWN, ROOK_PROMOTION_CAPTURE
                    );

                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_PAWN, BISHOP_PROMOTION_CAPTURE
                    );

                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_PAWN, KNIGHT_PROMOTION_CAPTURE
                    );
                }else{
                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_PAWN, CAPTURE);
                }

                attack = CLEAR_BIT_ON_BITBOARD(attack, target_square);
            }

            black_pawns = CLEAR_BIT_ON_BITBOARD(black_pawns, source_square);
        }
    
    
        // En Passant capture
        Square en_passant_square = (Square)(board_state->en_passant_target_square);
        if (en_passant_square != -1)
        {
            Bitboard source_attack = pre_calculated_pawn_attacks[WHITE][en_passant_square] & board_state->black_pawns;

            while (source_attack)
            {
                Square pawn_square = GET_LSB_INDEX(source_attack);
                moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                    pawn_square,
                    en_passant_square,
                    BLACK_PAWN,
                    EN_PASSANT_CAPTURE
                );
                source_attack = CLEAR_BIT_ON_BITBOARD(source_attack, pawn_square);
            }
        }
    }

    
}

void generate_all_pawns_capture_moves_from_game_state(Game* game, MoveList* move_list)
{
    if (game->turn ==  WHITE_TURN)
    {
        Bitboard white_pawns = game->white_pawns;
        Square source_square, target_square;

        while(white_pawns){
            source_square = GET_LSB_INDEX(white_pawns);

            // Pawn attacks
            Bitboard attack = pre_calculated_pawn_attacks[WHITE][source_square] & BLACK_OCCUPENCY(game);
            while(attack){
                target_square = GET_LSB_INDEX(attack);

                move_list->moves[move_list->current_index++] = CREATE_MOVE(
                    source_square,
                    target_square,
                    WHITE_PAWN, CAPTURE);
                

                attack = CLEAR_BIT_ON_BITBOARD(attack, target_square);
            }

            white_pawns = CLEAR_BIT_ON_BITBOARD(white_pawns, source_square);
        }

        Square en_passant_square = (Square)(game->en_passant_target_square);
        if (en_passant_square != -1)
        {
            Bitboard source_attack = pre_calculated_pawn_attacks[BLACK][en_passant_square] & game->white_pawns;

            while (source_attack)
            {
                Square pawn_square = GET_LSB_INDEX(source_attack);
                move_list->moves[move_list->current_index++] = CREATE_MOVE(
                    pawn_square,
                    en_passant_square,
                    WHITE_PAWN,
                    EN_PASSANT_CAPTURE
                );
                source_attack = CLEAR_BIT_ON_BITBOARD(source_attack, pawn_square);
            }
        }
    } else {
        Bitboard black_pawns = game->black_pawns;
        Square source_square, target_square;

        while(black_pawns){
            source_square = GET_LSB_INDEX(black_pawns);

            // Pawn attacks
            Bitboard attack = pre_calculated_pawn_attacks[BLACK][source_square] & WHITE_OCCUPENCY(game);
            while(attack){
                target_square = GET_LSB_INDEX(attack);

                move_list->moves[move_list->current_index++] = CREATE_MOVE(
                    source_square,
                    target_square,
                    BLACK_PAWN, CAPTURE);
                
                attack = CLEAR_BIT_ON_BITBOARD(attack, target_square);
            }

            black_pawns = CLEAR_BIT_ON_BITBOARD(black_pawns, source_square);
        }
        // En Passant capture
        Square en_passant_square = (Square)(game->en_passant_target_square);
        if (en_passant_square != -1)
        {
            Bitboard source_attack = pre_calculated_pawn_attacks[WHITE][en_passant_square] & game->black_pawns;
            while (source_attack)
            {
                Square pawn_square = GET_LSB_INDEX(source_attack);
                move_list->moves[move_list->current_index++] = CREATE_MOVE(
                    pawn_square,
                    en_passant_square,
                    BLACK_PAWN,
                    EN_PASSANT_CAPTURE
                );
                source_attack = CLEAR_BIT_ON_BITBOARD(source_attack, pawn_square);
            }
        }
    }
}
