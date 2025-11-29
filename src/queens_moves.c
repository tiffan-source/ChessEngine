
#include "queens_moves.h"

void generate_all_queens_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard white_queens = board_state->white_queens;
    Bitboard black_queens = board_state->black_queens;
    Bitboard move, attack;

    if (board_state->turn == WHITE)
    {
        while(white_queens){;

            source_square = get_lsb_index(white_queens);

            move = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
                source_square,
            ALL_OCCUPENCY(board_state)
            ) | retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(board_state)
            );

            Bitboard str = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(board_state)
            );
            while(move){
                target_square = get_lsb_index(move);

                if((1ULL << target_square) & (WHITE_OCCUPENCY(board_state))){
                    move = clear_bit_on_bitboard(move, target_square);
                    continue;
                } else {
                    moves_list->moves[moves_list->current_index++] = create_move(
                        source_square,
                        target_square,
                        WHITE_QUEEN,
                        (1ULL << target_square) & (BLACK_OCCUPENCY(board_state)) ? CAPTURE : QUIET_MOVES
                    );
                    move = clear_bit_on_bitboard(move, target_square);
                }
            }

            white_queens = clear_bit_on_bitboard(white_queens, source_square);
        }
    } else {
        while(black_queens){
            source_square = get_lsb_index(black_queens);

            move = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(board_state)
            ) | retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(board_state)
            );

            while(move){
                target_square = get_lsb_index(move);

                if((1ULL << target_square) & (BLACK_OCCUPENCY(board_state))){
                    move = clear_bit_on_bitboard(move, target_square);
                    continue;
                } else {
                    moves_list->moves[moves_list->current_index++] = create_move(
                        source_square,
                        target_square,
                        BLACK_QUEEN,
                        (1ULL << target_square) & (WHITE_OCCUPENCY(board_state)) ? CAPTURE : QUIET_MOVES
                    );
                    move = clear_bit_on_bitboard(move, target_square);
                }
            }
            black_queens = clear_bit_on_bitboard(black_queens, source_square);
        }
    }
}