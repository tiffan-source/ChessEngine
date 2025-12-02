
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
    generate_all_pawns_moves_from_game_state(game, move_list);
    generate_all_rooks_moves_from_game_state(game, move_list);
    generate_all_knight_moves_from_game_state(game, move_list);
    generate_all_bishop_moves_from_game_state(game, move_list);
    generate_all_queens_moves_from_game_state(game, move_list);
    generate_all_king_castling_moves_from_game_state(game, move_list);
    generate_all_king_quiet_and_capture_moves_from_game_state(game, move_list);
}

U64 generate_moves_from_position_at_depth(Game* game, int depth)
{
    U64 result = 0;
    MoveList* move_list = malloc(sizeof(MoveList));
    move_list->current_index = 0;

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);

    for (int i = 0; i < move_list->current_index; i++)
    {
        Game* game_cp = (Game*) malloc(sizeof(Game));
        *game_cp = *game;

        make_move(game_cp, move_list->moves[i]);

        if(!is_king_attacked(game_cp, game_cp->turn == WHITE_TURN ? WHITE : BLACK)){
            if(depth > 1){
                result += generate_moves_from_position_at_depth(game_cp, depth - 1);
            }else{
                result++;
            }
        }

        free(game_cp);
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
    printf("Depth %d:\n", depth);

    generate_all_pseudo_legal_moves_from_game_state(game, move_list);

    for (int i = 0; i < move_list->current_index; i++)
    {
        Game* game_cp = (Game*) malloc(sizeof(Game));
        *game_cp = *game;

        make_move(game_cp, move_list->moves[i]);

        if(!is_king_attacked(game_cp, game_cp->turn == WHITE_TURN ? WHITE : BLACK)){
            if(depth > 1){
                new_node = generate_moves_from_position_at_depth(game_cp, depth - 1);
                result += new_node;
                if(depth == original_depth){
                    printf("Move ");
                    print_move_as_uci(move_list->moves[i]);
                    printf(": %llu\n", new_node);
                }
            }else{
                result++;
                if (original_depth == 1)
                {
                    printf("Move ");
                    print_move_as_uci(move_list->moves[i]);
                    printf(": 1\n");
                }
            }
        }

        free(game_cp);
    }

    free(move_list);

    printf("Total nodes at depth %d: %llu\n", depth, result);
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
            return move_list->moves[i];
        }
    }

    return 0; // Return 0 if no matching move is found
}