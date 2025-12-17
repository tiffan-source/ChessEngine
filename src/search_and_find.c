
#include "search_and_find.h"

U64 nodes_searched = 0;

int Quiesce(Game* game, int alpha, int beta ) {
    int static_eval = material_evaluation_for_side(game);
    int score;

    // Stand Pat
    int best_value = static_eval;
    if( best_value >= beta )
        return best_value;
    if( best_value > alpha )
        alpha = best_value;

    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_capture_moves_from_game_state(game, &moves_list);
    
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


ScoredMove call_search_algorithm(Game* game, int depth)
{
    ScoredMove scored_move;
    nodes_searched = 0;
    
    PV pv = { .move_count = 0 };
    
    scored_move = nega_alpha_beta(game, depth, MIN, MAX, &pv);
    
    printf("\npv: ");
    for (int i = 0; i < pv.move_count; i++)
    {
        print_move_as_uci(pv.moves[i]);
        printf(" ");
    }
    printf("\n");
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

    nodes_searched++;

    if(depth == 0)
    {
        pv->move_count = 0;
        scored_move = (ScoredMove) { .score = Quiesce(game, alpha, beta) };
        return scored_move;
    }

    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_moves_from_game_state(game, &moves_list);
    order_move_using_mvv_lva(game, &moves_list);

    for (int i = 0; i < moves_list.current_index; i++)
    {
        Game new_game_state;
        memcpy(&new_game_state, game, sizeof(Game));
        make_move(&new_game_state, moves_list.moves[i].move);

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
            scored_move = (ScoredMove){ .score = MIN + (GET_DEPTH_FROM_CONFIG(get_config()) - depth) };
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
