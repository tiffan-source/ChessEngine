
#include "queens_moves.h"

void generate_all_queens_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard white_queens = board_state->white_queens;
    Bitboard black_queens = board_state->black_queens;
    Bitboard move, attack;
    Bitboard all_occupency = ALL_OCCUPENCY(board_state), black_occupency = BLACK_OCCUPENCY(board_state), white_occupency = WHITE_OCCUPENCY(board_state);
    Bitboard pre_calculated_queen_moves;

    if (board_state->turn == WHITE)
    {
        while(white_queens){;

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

                moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
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

                moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                    source_square,
                    target_square,
                    WHITE_QUEEN,
                    CAPTURE
                );

                attack = CLEAR_BIT_ON_BITBOARD(attack, target_square); 
            }

            white_queens = CLEAR_BIT_ON_BITBOARD(white_queens, source_square);
        }
    } else {
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

                moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                    source_square,
                    target_square,
                    BLACK_QUEEN,
                    QUIET_MOVES
                );
                move = CLEAR_BIT_ON_BITBOARD(move, target_square);
                
            }

            while(attack){
                target_square = GET_LSB_INDEX(attack);

                moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
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
}

void generate_all_queens_captures_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard white_queens = board_state->white_queens;
    Bitboard black_queens = board_state->black_queens;
    Bitboard move, attack;
    Bitboard all_occupency = ALL_OCCUPENCY(board_state);

    if (board_state->turn == WHITE)
    {
        while(white_queens){;

            source_square = GET_LSB_INDEX(white_queens);

            move = (retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
                source_square,
            all_occupency
            ) | retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
                source_square,
                all_occupency
            )) & BLACK_OCCUPENCY(board_state);

            while(move){
                target_square = GET_LSB_INDEX(move);

                moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                    source_square,
                    target_square,
                    WHITE_QUEEN,
                    CAPTURE
                );
                move = CLEAR_BIT_ON_BITBOARD(move, target_square);
            }

            white_queens = CLEAR_BIT_ON_BITBOARD(white_queens, source_square);
        }
    } else {
        while(black_queens){
            source_square = GET_LSB_INDEX(black_queens);

            move = (retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
                source_square,
                all_occupency
            ) | retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(board_state)
            )) & WHITE_OCCUPENCY(board_state);

            while(move){
                target_square = GET_LSB_INDEX(move);

                moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
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
}
