
#include "queens_moves.h"

void generate_all_white_queens_moves(Bitboard white_queens, Bitboard black_occupency, Bitboard all_occupency, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard move, attack;
    Bitboard pre_calculated_queen_moves;

    while(white_queens){
        source_square = GET_LSB_INDEX(white_queens);

        pre_calculated_queen_moves = (retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
            source_square,
            all_occupency
        ) | retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
            source_square,
            all_occupency
        ));

        move = pre_calculated_queen_moves & ~all_occupency;
        attack = pre_calculated_queen_moves & black_occupency;

        while(move){
            target_square = GET_LSB_INDEX(move);

            moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
                source_square,
                target_square,
                WHITE_QUEEN,
                QUIET_MOVES
            );
            move = CLEAR_BIT_ON_BITBOARD(move, target_square); 
        }

        while(attack)
        {
            target_square = GET_LSB_INDEX(attack);

            moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
                source_square,
                target_square,
                WHITE_QUEEN,
                CAPTURE
            );

            attack = CLEAR_BIT_ON_BITBOARD(attack, target_square); 
        }

        white_queens = CLEAR_BIT_ON_BITBOARD(white_queens, source_square);
    }
}

void generate_all_black_queens_moves(Bitboard black_queens, Bitboard white_occupency, Bitboard all_occupency, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard move, attack;
    Bitboard pre_calculated_queen_moves;

    while(black_queens){
        source_square = GET_LSB_INDEX(black_queens);

        pre_calculated_queen_moves = (retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
            source_square,
            all_occupency
        ) | retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
            source_square,
            all_occupency
        ));

        move = pre_calculated_queen_moves & ~all_occupency;
        attack = pre_calculated_queen_moves & white_occupency;

        while(move){
            target_square = GET_LSB_INDEX(move);

            moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
                source_square,
                target_square,
                BLACK_QUEEN,
                QUIET_MOVES
            );
            move = CLEAR_BIT_ON_BITBOARD(move, target_square);
        }

        while(attack){
            target_square = GET_LSB_INDEX(attack);

            moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
                source_square,
                target_square,
                BLACK_QUEEN,
                CAPTURE
            );
            attack = CLEAR_BIT_ON_BITBOARD(attack, target_square);
        }
        black_queens = CLEAR_BIT_ON_BITBOARD(black_queens, source_square);
    }
}

void generate_all_white_queens_captures(Bitboard white_queens, Bitboard black_occupency, Bitboard all_occupency, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard move;

    while(white_queens){
        source_square = GET_LSB_INDEX(white_queens);

        move = (retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
            source_square,
            all_occupency
        ) | retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
            source_square,
            all_occupency
        )) & black_occupency;

        while(move){
            target_square = GET_LSB_INDEX(move);

            moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
                source_square,
                target_square,
                WHITE_QUEEN,
                CAPTURE
            );
            move = CLEAR_BIT_ON_BITBOARD(move, target_square);
        }

        white_queens = CLEAR_BIT_ON_BITBOARD(white_queens, source_square);
    }
}

void generate_all_black_queens_captures(Bitboard black_queens, Bitboard white_occupency, Bitboard all_occupency, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard move;

    while(black_queens){
        source_square = GET_LSB_INDEX(black_queens);

        move = (retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
            source_square,
            all_occupency
        ) | retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
            source_square,
            all_occupency
        )) & white_occupency;

        while(move){
            target_square = GET_LSB_INDEX(move);

            moves_list->moves[moves_list->current_index++] = CREATE_SCORED_MOVE(
                source_square,
                target_square,
                BLACK_QUEEN,
                CAPTURE
            );
            move = CLEAR_BIT_ON_BITBOARD(move, target_square);
        }
        black_queens = CLEAR_BIT_ON_BITBOARD(black_queens, source_square);
    }
}
