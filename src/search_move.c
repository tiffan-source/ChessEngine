
#include "search_move.h"

U64 nodes_searched = 0;

int quiesce(Game* game, int alpha, int beta ) {
    int static_eval = material_evaluation_with_piece_square_table_for_side(game);

    int score;

    // Stand Pat
    int best_value = static_eval;
    if( best_value >= beta )
        return best_value;
    if( best_value > alpha )
        alpha = best_value;

    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_capture_moves_from_game_state(game, &moves_list);
    order_move(game, &moves_list, 0, 0); // Ply et follow_pv est inutile ici car pas necessaire pour sort les captures

    for (int i = 0; i < moves_list.current_index; i++)
    {
        Game new_game_state = *game;
        make_move(&new_game_state, moves_list.moves[i].move);
        nodes_searched++;

        if(!is_king_attacked_by_side(&new_game_state, new_game_state.turn)){ // Little hack here Side and TURN are aligned

            score = -quiesce(&new_game_state, -beta, -alpha);

            if( score >= beta )
                return score;
            if( score > best_value )
                best_value = score;
            if( score > alpha )
                alpha = score;
        }
    }

    return best_value;
}

void print_info_at_end_of_search(Game* game, int depth, ScoredMove scored_move, int end_time)
{
    int move_to_show = depth;

    printf("info ");
    printf("depth %d ", depth);
    printf("score ");
    
    if(scored_move.score <= MIN + depth)
    {
        printf("mate %ld ", (scored_move.score - MIN + 1) / 2);
    }
    else if (scored_move.score >= MAX - depth)
    {
        printf("mate -%ld ", (MAX - scored_move.score + 1) / 2);
    }
    else
    {
        printf("cp %ld ", scored_move.score);
    }


    printf(" nodes %llu ", nodes_searched);
    printf("time %d ", end_time);

    printf("pv ");
    for (int i = 0; i < pv_length[0]; i++)
    {
        print_move_as_uci(pv_list[0][i]);
        printf(" ");
    }
    printf("\n");
}


ScoredMove call_search_algorithm(Game* game, int depth)
{
    ScoredMove scored_move;
    int cumulative_time = 0;
    nodes_searched = 0;

    initialize_transposition_table();
    reset_killer_moves();
    reset_history_heuristic();
    
    for (int curr_depth = 1; curr_depth <= depth; curr_depth++)
    {
        // printf("Starting search at depth %d\n", curr_depth);
        set_depth(curr_depth);
        int start_time = get_time_ms();
        if(curr_depth > 1)
        {
            memcpy(old_pv_list, pv_list, sizeof(pv_list));
            memcpy(old_pv_length, pv_length, sizeof(pv_length));
        }
        scored_move = nega_alpha_beta(game, curr_depth, MIN, MAX, curr_depth > 1);
        int end_time = get_time_ms() - start_time;
        cumulative_time += end_time;

        print_info_at_end_of_search(game, curr_depth, scored_move, cumulative_time);
    }

    free_transposition_table();

    return scored_move;
}

U64 get_nodes_searched()
{
    return nodes_searched;
}

ScoredMove nega_alpha_beta(Game *game, int depth, int alpha, int beta, int following_pv)
{
    int move_found = 0;
    int max = MIN;
    Move best_move = 0;
    ScoredMove scored_move;
    int ply = get_depth() - depth;
    int original_alpha = alpha;

    // Probe TT
    TTEntry entry = probe(game->zobrist_key, depth, alpha, beta);
    if (entry.flag != TT_NOT_FOUND) {
        pv_length[ply] = 0;
        return entry.best_move;
    }

    if(depth == 0)
    {
        pv_length[ply] = 0;
        scored_move = (ScoredMove) { .score = quiesce(game, alpha, beta) };
        return scored_move;
    }

    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_moves_from_game_state(game, &moves_list);
    order_move(game, &moves_list, ply, following_pv);

    // Print all moves for debugging
    // printf("Depth %d Moves: ", depth);
    // for (int i = 0; i < moves_list.current_index; i++)
    // {
    //     print_move_as_uci(moves_list.moves[i].move);
    //     printf(" ");
    // }
    // printf("\n");
    // printf("Following PV: %d\n", following_pv);
    

    for (int i = 0; i < moves_list.current_index; i++)
    {
        Game new_game_state;
        memcpy(&new_game_state, game, sizeof(Game));
        make_move(&new_game_state, moves_list.moves[i].move);

        nodes_searched++;
        
        if(!is_king_attacked_by_side(&new_game_state, new_game_state.turn)){ // Little hack here Side and TURN are aligned
            move_found = 1;
            scored_move = nega_alpha_beta(&new_game_state, depth - 1, -beta, -alpha, following_pv && i == 0 && old_pv_length[ply + 1] > 0);
            scored_move.score *= -1;

            if (scored_move.score > max)
            {
                max = scored_move.score;
                best_move = moves_list.moves[i].move;


                if (max > alpha)
                {
                    alpha = max;

                    // Update PV
                    pv_list[ply][0] = best_move;
                    memcpy(&pv_list[ply][1], &pv_list[ply + 1][0], pv_length[ply + 1] * sizeof(Move));
                    pv_length[ply] = pv_length[ply + 1] + 1;
                }
                if (beta <= alpha)
                {
                    if (GET_MOVE_TYPE_FROM_MOVE(best_move) != CAPTURE)
                        update_history_heuristic(moves_list.moves + i, 300 * depth - 250);

                    add_killer_move_at_ply(best_move, ply);
                    break;
                }
            }
        }
    }

    if (!move_found)
    {
        pv_length[ply] = 0;
        // Check for checkmate or stalemate
        if (is_king_attacked_by_side(game, !game->turn))
        {
            scored_move = (ScoredMove){ .score = MIN + ply };
            return scored_move;
        }
        else
        {
            scored_move = (ScoredMove){ .score = 0 };
            return scored_move; // Stalemate
        }
    }

    scored_move.score = max;
    scored_move.move = best_move;

    if(scored_move.score <= original_alpha)
    {
        record(game->zobrist_key, depth, scored_move, TT_UPPERBOUND);
    }
    else if (scored_move.score >= beta)
    {
        record(game->zobrist_key, depth, scored_move, TT_LOWERBOUND);
    }
    else
    {
        record(game->zobrist_key, depth, scored_move, TT_EXACT);
    }

    return scored_move;
}
