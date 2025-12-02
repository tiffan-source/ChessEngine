
#include "uci_commands.h"

void handle_uci_command(char* response)
{
    snprintf(response, UCI_RESPONSE_MAX_LENGTH,
             "id name UpYourChess\n"
             "id author BlackGenius\n"
             "uciok\n");
}

void handle_isready_command(char* response)
{
    snprintf(response, UCI_RESPONSE_MAX_LENGTH, "readyok\n");
}

void handle_position_command(Game** game, const char* input)
{
    char* token_moves = NULL;
    size_t input_len = strlen(input);
    char* input_copy = malloc(input_len + 1);
    memcpy(input_copy, input, input_len + 1);

    char* startpsos_str = strstr(input_copy, "startpos");
    char* fen_str = strstr(input_copy, "fen ");

    if(*game != NULL)
    {
        free_game(*game);
        *game = NULL;
    }

    if(startpsos_str != NULL)
    {
        *game = create_game();   
    } else if(fen_str != NULL)
    {
        *game = create_game_from_FEN(fen_str + 4);   
    }

    char* moves_str = strstr(input_copy, "moves ");

    if (moves_str == NULL)
    {
        free(input_copy);
        return;
    }

    // initialize tokenization for moves
    token_moves = strtok(moves_str, " \n\r\t");

    while (token_moves = strtok(NULL, " \n\r\t"))
    {
        MoveList movelist = { .current_index = 0 };
        generate_all_pseudo_legal_moves_from_game_state(*game, &movelist);
        Move move = retrieve_uci_move_from_move_list(token_moves, &movelist);
        if (move == 0)
        {
            printf("Invalid move: %s\n", token_moves);
            continue;
        }
        make_move(*game, move);
    }

    free(input_copy);
}

void handle_go_command(Game* game, const char* input, char* response)
{
    ScoredMove result;
    char move_uci[6];
    int input_size = strlen(input);
    char *input_copy = malloc(input_size + 1);
    memcpy(input_copy, input, input_size + 1);

    char* perf = strstr(input_copy, "perft ");
    if (perf != NULL)
    {
        int depth = atoi(perf + 6);
        U64 nodes = test_helper_generate_moves_from_position_at_depth(game, depth, depth);
        snprintf(response, UCI_RESPONSE_MAX_LENGTH, "nodes %llu\n", nodes);
        free(input_copy);
        return;
    }

    if (game->turn == WHITE_TURN)
    {
        result = min_max_best_move_max(game, 5);    
    }else {
        result = min_max_best_move_min(game, 5);
    }
    build_move_as_uci(result.move, move_uci);

    snprintf(response, UCI_RESPONSE_MAX_LENGTH, "bestmove %s\n", move_uci);
}

void handle_quit_command(char* response)
{
    snprintf(response, UCI_RESPONSE_MAX_LENGTH, "QUIT\n");

}

void handle_command(Game** game, const char* command, char* response)
{
    if (strncmp(command, "uci", 3) == 0)
    {
        handle_uci_command(response);
    } else if (strncmp(command, "isready", 7) == 0)
    {
        handle_isready_command(response);
    } else if (strncmp(command, "position", 8) == 0)
    {
        handle_position_command(game, command + 8);
    } else if (strncmp(command, "go", 2) == 0)
    {
        handle_go_command(*game, command, response);
    } else if(strncmp(command, "quit", 4) == 0)
    {
        handle_quit_command(response);
    }

}