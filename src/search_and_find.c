
#include "search_and_find.h"

// Function to find the best move using Min-Max algorithm with alpha-beta pruning

ScoredMove min_max_best_move_min(Game* game, int depth)
{
    int move_found = 0;
    int min = INT_MAX;
    Move min_move = 0;
    ScoredMove scored_move;

    if (depth == 0)
    {
        scored_move = (ScoredMove){ .score = -material_evaluation(game) };
        return scored_move;
    }
    
    MoveList moves_list = { .current_index = 0 };
    generate_all_pseudo_legal_moves_from_game_state(game, &moves_list);

    
    for (int i = 0; i < moves_list.current_index; i++)
    {
        Game* new_game_state = malloc(sizeof(Game));
        *new_game_state = *game;
        make_move(new_game_state, moves_list.moves[i]);

        if(!is_king_attacked(new_game_state, new_game_state->turn == WHITE_TURN ? WHITE : BLACK)){
            move_found = 1;
            scored_move = min_max_best_move_max(new_game_state, depth - 1);
            if (scored_move.score < min)
            {
                min = scored_move.score;
                min_move = moves_list.moves[i];
            }
        }
        free_game(new_game_state);
    }

    if (!move_found)
    {
        // Check for checkmate or stalemate
        if (is_king_attacked(game, game->turn == WHITE_TURN ? BLACK : WHITE))
        {
            scored_move = (ScoredMove){ .score = INT_MAX - 1 };
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
    int max = INT_MIN;
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
        Game* new_game_state = malloc(sizeof(Game));
        *new_game_state = *game;
        make_move(new_game_state, moves_list.moves[i]);

        if(!is_king_attacked(new_game_state, new_game_state->turn == WHITE_TURN ? WHITE : BLACK)){
            move_found = 1;
            scored_move = min_max_best_move_min(new_game_state, depth - 1);
            if (scored_move.score > max)
            {
                max = scored_move.score;
                max_move= moves_list.moves[i];
            }
        }
        free_game(new_game_state);
    }

    if (!move_found)
    {
        // Check for checkmate or stalemate
        if (is_king_attacked(game, game->turn == WHITE_TURN ? BLACK : WHITE))
        {
            scored_move = (ScoredMove){ .score = INT_MIN + 1 };
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