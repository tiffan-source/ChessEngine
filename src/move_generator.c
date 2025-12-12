
#include "move_generator.h"

int get_time_ms()
{
    struct timeval time_value;
    gettimeofday(&time_value, NULL);
    return time_value.tv_sec * 1000 + time_value.tv_usec / 1000;
}

void initialize_move_generation_databases()
{
    initialize_pre_calculated_bishop_moves_database();
    initialize_pre_calculated_rook_moves_database();
    initialize_pre_calculated_pawn_attacks_database();
    initialize_pre_calculated_pawn_moves_database();
}

void generate_all_pseudo_legal_moves_from_game_state(Game* game, MoveList* move_list)
{
    Bitboard all_occupency = ALL_OCCUPENCY(game);
    Bitboard white_occupency = WHITE_OCCUPENCY(game);
    Bitboard black_occupency = BLACK_OCCUPENCY(game);
    Square en_passant_square = game->en_passant_target_square;

    if (game->turn ==  WHITE_TURN)
    {
        generate_all_white_pawns_moves(game->white_pawns, black_occupency, all_occupency, en_passant_square, move_list);
        generate_all_white_rooks_moves(game->white_rooks, black_occupency, all_occupency, move_list);
        generate_all_white_knight_moves(game->white_knights, black_occupency, all_occupency, move_list);
        generate_all_white_bishop_moves(game->white_bishops, black_occupency, all_occupency, move_list);
        generate_all_white_queens_moves(game->white_queens, black_occupency, all_occupency, move_list);
        generate_all_white_king_castling_moves_from_game_state(game, move_list);
        generate_all_white_king_quiet_and_capture_moves(game->white_king, black_occupency, all_occupency, move_list);
    }else {
        generate_all_black_pawns_moves(game->black_pawns, white_occupency, all_occupency, en_passant_square, move_list);
        generate_all_black_rooks_moves(game->black_rooks, white_occupency, all_occupency, move_list);
        generate_all_black_knight_moves(game->black_knights, white_occupency, all_occupency, move_list);
        generate_all_black_bishop_moves(game->black_bishops, white_occupency, all_occupency, move_list);
        generate_all_black_queens_moves(game->black_queens, white_occupency, all_occupency, move_list);
        generate_all_black_king_castling_moves_from_game_state(game, move_list);
        generate_all_black_king_quiet_and_capture_moves(game->black_king, white_occupency, all_occupency, move_list);
    }
}

void generate_all_capture_moves_from_game_state(Game* game, MoveList* move_list)
{
    Bitboard all_occupency = ALL_OCCUPENCY(game);
    Bitboard white_occupency = WHITE_OCCUPENCY(game);
    Bitboard black_occupency = BLACK_OCCUPENCY(game);
    Square en_passant_square = game->en_passant_target_square;

    if(game->turn == WHITE_TURN)
    {
        generate_all_white_pawns_capture_moves(game->white_pawns, black_occupency, all_occupency, en_passant_square, move_list);
        generate_all_white_rooks_captures(game->white_rooks, black_occupency, all_occupency, move_list);
        generate_all_white_knight_captures(game->white_knights, black_occupency, move_list);
        generate_all_white_bishop_captures(game->white_bishops, black_occupency, all_occupency, move_list);
        generate_all_white_queens_captures(game->white_queens, black_occupency, all_occupency, move_list);
        generate_all_white_king_capture_moves(game->white_king, black_occupency, move_list);
    }else{
        generate_all_black_pawns_capture_moves(game->black_pawns, white_occupency, all_occupency, en_passant_square, move_list);
        generate_all_black_rooks_captures(game->black_rooks, white_occupency, all_occupency, move_list);
        generate_all_black_knight_captures(game->black_knights, white_occupency, move_list);
        generate_all_black_bishop_captures(game->black_bishops, white_occupency, all_occupency, move_list);
        generate_all_black_queens_captures(game->black_queens, white_occupency, all_occupency, move_list);
        generate_all_black_king_capture_moves(game->black_king, white_occupency, move_list);
    }
}

U64 generate_moves_from_position_at_depth(Game* game, int depth)
{
    U64 result = 0;
    MoveList* move_list = malloc(sizeof(MoveList));
    move_list->current_index = 0;

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);

    for (int i = 0; i < move_list->current_index; i++)
    {
        Game new_game = make_move(*game, move_list->moves[i].move);

        if(!is_king_attacked_by_side(&new_game, new_game.turn)){ // Little hack here Side and TURN are aligned
            if(depth > 1){
                result += generate_moves_from_position_at_depth(&new_game, depth - 1);
            }else{
                result++;
            }
        }

    }

    free(move_list);
    
    return result;
}

U64 test_helper_generate_moves_from_position_at_depth(Game* game, int depth, int original_depth)
{
    U64 result = 0, old_node = 0, new_node = 0;
    MoveList* move_list = malloc(sizeof(MoveList));
    move_list->current_index = 0;

    int init_time = get_time_ms();

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);

    for (int i = 0; i < move_list->current_index; i++)
    {
        Game new_game = make_move(*game, move_list->moves[i].move);

        if(!is_king_attacked_by_side(&new_game, new_game.turn)){ // Little hack here Side and TURN are aligned  
            if(depth > 1){
                new_node = generate_moves_from_position_at_depth(&new_game, depth - 1);
                result += new_node;
            }else{
                result++;
            }
        }

    }

    free(move_list);

    int end_time = get_time_ms() - init_time;
    printf("End time: %d ms\n", end_time);

    return result;
}

Move retrieve_uci_move_from_move_list(const char* uci_move_str, MoveList* move_list)
{
    for (int i = 0; i < move_list->current_index; i++)
    {
        Square from_square = GET_SOURCE_SQUARE(move_list->moves[i]);
        Square to_square = GET_DESTINATION_SQUARE(move_list->moves[i]);
        char promotion_char = '\0';
        switch (GET_MOVE_TYPE(move_list->moves[i]))
        {
            case QUEEN_PROMOTION:
            case QUEEN_PROMOTION_CAPTURE:
                promotion_char = 'q';
                break;

            case ROOK_PROMOTION:
            case ROOK_PROMOTION_CAPTURE:
                promotion_char = 'r';
                break;

            case BISHOP_PROMOTION:
            case BISHOP_PROMOTION_CAPTURE:
                promotion_char = 'b';
                break;

            case KNIGHT_PROMOTION:
            case KNIGHT_PROMOTION_CAPTURE:
                promotion_char = 'n';
                break;

            default:
                break;
        }

        char generated_uci_str[6];
        snprintf(generated_uci_str, sizeof(generated_uci_str), "%s%s%c",
                 square_to_string[from_square],
                 square_to_string[to_square],
                 promotion_char);


        if (strcmp(uci_move_str, generated_uci_str) == 0)
        {
            return move_list->moves[i].move;
        }
    }

    return 0; // Return 0 if no matching move is found
}