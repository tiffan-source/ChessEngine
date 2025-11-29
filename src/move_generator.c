
#include "move_generator.h"

int get_time_ms()
{
    struct timeval time_value;
    gettimeofday(&time_value, NULL);
    return time_value.tv_sec * 1000 + time_value.tv_usec / 1000;
}


void generate_all_moves_from_game_state(Game* game, MoveList* move_list)
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

    generate_all_moves_from_game_state(game, move_list);

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

    // result = move_list->current_index;

    free(move_list);
    
    return result;
}

U64 test_helper_generate_moves_from_position_at_depth(Game* game, int depth, int original_depth)
{
    U64 result = 0, old_node = 0, new_node = 0;
    MoveList* move_list = malloc(sizeof(MoveList));
    move_list->current_index = 0;

    generate_all_moves_from_game_state(game, move_list);

    for (int i = 0; i < move_list->current_index; i++)
    {
        Game* game_cp = (Game*) malloc(sizeof(Game));
        *game_cp = *game;

        make_move(game_cp, move_list->moves[i]);

        if(!is_king_attacked(game_cp, game_cp->turn == WHITE_TURN ? WHITE : BLACK)){
            if(depth > 1){
                new_node = test_helper_generate_moves_from_position_at_depth(game_cp, depth - 1, original_depth);
                result += new_node;
                if(depth == original_depth){
                    printf("Move %s ", move_type_to_string[GET_MOVE_TYPE(move_list->moves[i])]);
                    print_move_as_uci(move_list->moves[i]);
                    printf(": %llu\n", new_node);
                }
            }else{
                result++;
                if (original_depth == 1)
                {
                    printf("Move %s ", move_type_to_string[GET_MOVE_TYPE(move_list->moves[i])]);
                    print_move_as_uci(move_list->moves[i]);
                    printf(": 1\n");
                }
            }
        }

        free(game_cp);
    }

    free(move_list);

    return result;
}