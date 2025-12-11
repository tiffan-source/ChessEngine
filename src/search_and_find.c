
#include "search_and_find.h"

// Function to find the best move using Min-Max algorithm with alpha-beta pruning

ScoredMove min_max_best_move_min(Game* game, int depth)
{
    int move_found = 0;
    int min = MAX;
    Move min_move = 0;
    ScoredMove scored_move;

    if (depth == 0)
    {
        scored_move = (ScoredMove){ .score = material_evaluation(game) };
        return scored_move;
    }
    
    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_moves_from_game_state(game, &moves_list);

    
    for (int i = 0; i < moves_list.current_index; i++)
    {

        Game new_game_state = make_move(*game, moves_list.moves[i].move);

        if(!is_king_attacked_by_side(&new_game_state, new_game_state.turn == WHITE_TURN ? WHITE : BLACK)){
            move_found = 1;
            scored_move = min_max_best_move_max(&new_game_state, depth - 1);
            if (scored_move.score < min)
            {
                min = scored_move.score;
                min_move = moves_list.moves[i].move;
            }
        }
    }

    if (!move_found)
    {
        // Check for checkmate or stalemate
        if (is_king_attacked_by_side(game, game->turn == WHITE_TURN ? BLACK : WHITE))
        {
            scored_move = (ScoredMove){ .score = MAX - (GET_DEPTH_FROM_CONFIG(get_config()) - depth) };
            return scored_move; // Checkmate
        }
        else
        {
            scored_move = (ScoredMove){ .score = 0 };
            return scored_move; // Stalemate
        }
    }
    scored_move.score = min;
    scored_move.move = min_move;
    return scored_move;
}

ScoredMove min_max_best_move_max(Game* game, int depth)
{
    int move_found = 0;
    int max = MIN;
    Move max_move = 0;
    ScoredMove scored_move;

    if (depth == 0)
    {
        scored_move = (ScoredMove){ .score = material_evaluation(game) };
        return scored_move;
    }
    
    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_moves_from_game_state(game, &moves_list);


    for (int i = 0; i < moves_list.current_index; i++)
    {
        Game new_game_state = make_move(*game, moves_list.moves[i].move);

        if(!is_king_attacked_by_side(&new_game_state, new_game_state.turn == WHITE_TURN ? WHITE : BLACK)){
            move_found = 1;
            scored_move = min_max_best_move_min(&new_game_state, depth - 1);
            if (scored_move.score > max)
            {
                max = scored_move.score;
                max_move= moves_list.moves[i].move;
            }
        }
    }

    if (!move_found)
    {
        // Check for checkmate or stalemate
        if (is_king_attacked_by_side(game, game->turn == WHITE_TURN ? BLACK : WHITE))
        {
            scored_move = (ScoredMove){ .score = MIN + (GET_DEPTH_FROM_CONFIG(get_config()) - depth) };
            return scored_move; // Checkmate
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

//Function to find the best move using Negamax algorithm
ScoredMove negamax_best_move(Game* game, int depth)
{
    int move_found = 0;
    int max = MIN;
    Move max_move = 0;
    ScoredMove scored_move;

    if(depth == 0)
    {
        ScoredMove scored_move = { .score = material_evaluation_for_side(game) };
        return scored_move;
    }

      
    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_moves_from_game_state(game, &moves_list);

    for (int i = 0; i < moves_list.current_index; i++)
    {
        Game new_game_state = make_move(*game, moves_list.moves[i].move);

        if(!is_king_attacked_by_side(&new_game_state, new_game_state.turn == WHITE_TURN ? WHITE : BLACK)){
            move_found = 1;
            scored_move = negamax_best_move(&new_game_state, depth - 1);
            if (scored_move.score * -1 > max)
            {
                max = scored_move.score * -1;
                max_move = moves_list.moves[i].move;
            }
        }
    }

    if (!move_found)
    {
        // Check for checkmate or stalemate
        int white_turn = game->turn == WHITE_TURN;
        if (is_king_attacked_by_side(game, white_turn ? BLACK : WHITE))
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

// Function to find the best move using Min-Max algorithm with alpha-beta pruning

ScoredMove alpha_beta_min(Game* game, int depth, int alpha, int beta)
{
    int move_found = 0;
    int min = MAX;
    Move min_move = 0;
    ScoredMove scored_move;

    if (depth == 0)
    {
        scored_move = (ScoredMove){ .score = material_evaluation(game) };
        return scored_move;
    }
    
    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_moves_from_game_state(game, &moves_list);

    for (int i = 0; i < moves_list.current_index; i++)
    {

        Game new_game_state = make_move(*game, moves_list.moves[i].move);

        if(!is_king_attacked_by_side(&new_game_state, new_game_state.turn == WHITE_TURN ? WHITE : BLACK)){
            move_found = 1;
            scored_move = alpha_beta_max(&new_game_state, depth - 1, alpha, beta);
            if (scored_move.score < min)
            {
                min = scored_move.score;
                min_move = moves_list.moves[i].move;
                if (min < beta)
                {
                    beta = min;
                }
                if (beta <= alpha)
                {
                    break; // Alpha-beta pruning
                }
            }
        }
    }

    if (!move_found)
    {
        // Check for checkmate or stalemate
        if (is_king_attacked_by_side(game, game->turn == WHITE_TURN ? BLACK : WHITE))
        {
            scored_move = (ScoredMove){ .score = MAX - (GET_DEPTH_FROM_CONFIG(get_config()) - depth) };
            return scored_move; // Checkmate
        }
        else
        {
            scored_move = (ScoredMove){ .score = 0 };
            return scored_move; // Stalemate
        }
    }
    scored_move.score = min;
    scored_move.move = min_move;
    return scored_move;
}

ScoredMove alpha_beta_max(Game* game, int depth, int alpha, int beta)
{
    int move_found = 0;
    int max = MIN;
    Move max_move = 0;
    ScoredMove scored_move;

    if (depth == 0)
    {
        scored_move = (ScoredMove){ .score = material_evaluation(game) };
        return scored_move;
    }
    
    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_moves_from_game_state(game, &moves_list);


    for (int i = 0; i < moves_list.current_index; i++)
    {
        Game new_game_state = make_move(*game, moves_list.moves[i].move);

        if(!is_king_attacked_by_side(&new_game_state, new_game_state.turn == WHITE_TURN ? WHITE : BLACK)){
            move_found = 1;
            scored_move = alpha_beta_min(&new_game_state, depth - 1, alpha, beta);
            if (scored_move.score > max)
            {
                max = scored_move.score;
                max_move = moves_list.moves[i].move;
                if (max > alpha)
                {
                    alpha = max;
                }
                if (beta <= alpha)
                {
                    break; // Alpha-beta pruning
                }
            }
        }
    }

    if (!move_found)
    {
        // Check for checkmate or stalemate
        if (is_king_attacked_by_side(game, game->turn == WHITE_TURN ? BLACK : WHITE))
        {
            scored_move = (ScoredMove){ .score = MIN + (GET_DEPTH_FROM_CONFIG(get_config()) - depth) };
            return scored_move; // Checkmate
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

ScoredMove nega_alpha_beta(Game *game, int depth, int alpha, int beta)
{
    int move_found = 0;
    int max = MIN;
    Move max_move = 0;
    ScoredMove scored_move;

    if(depth == 0)
    {
        ScoredMove scored_move = { .score = material_evaluation_for_side(game) };
        return scored_move;
    }

      
    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_moves_from_game_state(game, &moves_list);

    for (int i = 0; i < moves_list.current_index; i++)
    {
        Game new_game_state = make_move(*game, moves_list.moves[i].move);

        if(!is_king_attacked_by_side(&new_game_state, new_game_state.turn == WHITE_TURN ? WHITE : BLACK)){
            move_found = 1;
            scored_move = nega_alpha_beta(&new_game_state, depth - 1, -beta, -alpha);
            if (scored_move.score * -1 > max)
            {
                max = scored_move.score * -1;
                max_move = moves_list.moves[i].move;
                if (max > alpha)
                {
                    alpha = max;
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
        int white_turn = game->turn == WHITE_TURN;
        if (is_king_attacked_by_side(game, white_turn ? BLACK : WHITE))
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