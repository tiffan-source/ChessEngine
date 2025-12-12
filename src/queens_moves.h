
#ifndef QUEENS_MOVES_H
#define QUEENS_MOVES_H

#include "game.h"
#include "moves.h"
#include "rooks_moves.h"
#include "bishops_moves.h"

void generate_all_queens_moves_from_game_state(Game* board_state, MoveList* moves_list);
void generate_all_white_queens_moves_from_game_state(Game* board_state, MoveList* moves_list);
void generate_all_black_queens_moves_from_game_state(Game* board_state, MoveList* moves_list);

void generate_all_queens_captures_from_game_state(Game* board_state, MoveList* moves_list);
void generate_all_white_queens_captures_from_game_state(Game* board_state, MoveList* moves_list);
void generate_all_black_queens_captures_from_game_state(Game* board_state, MoveList* moves_list);

#endif // QUEENS_MOVES_H
