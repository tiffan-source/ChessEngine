
#include "search_and_find.h"

U64 nodes_searched = 0;

int Quiesce(Game* game, int alpha, int beta ) {
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
    order_move(game, &moves_list, 0); // Ply est inutile ici car pas necessaire pour sort les captures

    for (int i = 0; i < moves_list.current_index; i++)
    {
        Game new_game_state = *game;
        make_move(&new_game_state, moves_list.moves[i].move);
        nodes_searched++;

        if(!is_king_attacked_by_side(&new_game_state, new_game_state.turn)){ // Little hack here Side and TURN are aligned

            score = -Quiesce(&new_game_state, -beta, -alpha);

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

void print_info_at_end_of_search(int depth, ScoredMove scored_move, PV pv, int end_time)
{
    int move_to_show = depth;

    printf("info ");
    printf("depth %d ", depth);
    printf("score ");
    
    if(scored_move.score <= MIN + depth)
    {
        move_to_show = scored_move.score - MIN;
        printf("mate %ld ", (scored_move.score - MIN + 1) / 2);
    }
    else if (scored_move.score >= MAX - depth)
    {
        move_to_show = MAX - scored_move.score;
        printf("mate -%ld ", (MAX - scored_move.score + 1) / 2);
    }
    else
    {
        printf("cp %ld ", scored_move.score);
    }

    printf("nodes %llu ", nodes_searched);
    printf("time %d ", end_time);
    printf("pv ");
    for (int i = 0; i < move_to_show; i++)
    {
        print_move_as_uci(pv.moves[i]);
        printf(" ");
    }
    printf("\n");
}


ScoredMove call_search_algorithm(Game* game, int depth)
{
    ScoredMove scored_move;
    int cumulative_time = 0;
    nodes_searched = 0;

    reset_killer_moves();
    reset_history_heuristic();
    
    for (int curr_depth = 1; curr_depth <= depth; curr_depth++)
    {
        PV pv = { .move_count = 0 };

        int start_time = get_time_ms();
        scored_move = nega_alpha_beta(game, curr_depth, MIN, MAX, &pv);
        int end_time = get_time_ms() - start_time;
        cumulative_time += end_time;
        
        print_info_at_end_of_search(curr_depth, scored_move, pv, cumulative_time);
    }

    return scored_move;
}

U64 get_nodes_searched()
{
    return nodes_searched;
}

ScoredMove nega_alpha_beta(Game *game, int depth, int alpha, int beta, PV *pv)
{
    int move_found = 0;
    int max = MIN;
    Move max_move = 0;
    PV child_pv;
    ScoredMove scored_move;
    int ply = get_depth() - depth;

    if(depth == 0)
    {
        pv->move_count = 0;
        scored_move = (ScoredMove) { .score = Quiesce(game, alpha, beta) };
        return scored_move;
    }

    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_moves_from_game_state(game, &moves_list);
    order_move(game, &moves_list, ply);

    for (int i = 0; i < moves_list.current_index; i++)
    {
        Game new_game_state;
        memcpy(&new_game_state, game, sizeof(Game));
        make_move(&new_game_state, moves_list.moves[i].move);

        nodes_searched++;
        
        if(!is_king_attacked_by_side(&new_game_state, new_game_state.turn)){ // Little hack here Side and TURN are aligned
            move_found = 1;
            scored_move = nega_alpha_beta(&new_game_state, depth - 1, -beta, -alpha, &child_pv);

            if (scored_move.score * -1 > max)
            {
                max = scored_move.score * -1;
                max_move = moves_list.moves[i].move;

                if (max > alpha)
                {
                    alpha = max;

                    // Update PV
                    pv->moves[0] = max_move;
                    memcpy(pv->moves + 1, child_pv.moves, sizeof(Move) * child_pv.move_count);
                    pv->move_count = child_pv.move_count + 1;

                }
                if (beta <= alpha)
                {
                    if (GET_MOVE_TYPE_FROM_MOVE(max_move) != CAPTURE)
                        update_history_heuristic(moves_list.moves + i, 300 * depth - 250);

                    add_killer_move_at_ply(max_move, ply);
                    break;
                }
            }
        }
    }

    if (!move_found)
    {
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
    scored_move.move = max_move;
    return scored_move;
}
