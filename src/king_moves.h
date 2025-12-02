
#ifndef KING_MOVES_H
#define KING_MOVES_H

#include "board.h"
#include "moves.h"
#include "game.h"
#include "binary_tools.h"
#include "bishops_moves.h"
#include "rooks_moves.h"
#include "knights_moves.h"
#include "queens_moves.h"
#include "pieces.h"
#include "pawns_moves.h"

extern const Bitboard pre_calculated_king_moves[64];

Bitboard generate_king_moves_from_square(Square square);

void generate_all_king_quiet_and_capture_moves_from_game_state(Game* board_state, MoveList* moves_list);
void generate_all_king_castling_moves_from_game_state(Game* board_state, MoveList* moves_list);

/**
 * @brief Checks if a given square is attacked by the specified side.
 * 
 * @param board_state The current state of the game board.
 * @param square The square to check for attacks.
 * @param side Attack side
 * @return int Returns 1 if the square is attacked, 0 otherwise.
 */
int is_square_attacked(Game* board_state, Square square, Side side);

/**
 * @brief Checks if the king is attacked by the specified side.
 * 
* @param board_state The current state of the game board.
* @param side Attack side
* @return int Returns 1 if the king is attacked, 0 otherwise.
 */
int is_king_attacked(Game* board_state, Side side);

int is_king_mate(Game* board_state);

#endif // KING_MOVES_H
