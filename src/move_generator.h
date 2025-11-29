
#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "rooks_moves.h"
#include "knights_moves.h"
#include "bishops_moves.h"
#include "queens_moves.h"
#include "pawns_moves.h"
#include "king_moves.h"

U64 generate_moves_from_position_at_depth(Game* game, int depth);
int get_time_ms();
U64 test_helper_generate_moves_from_position_at_depth(Game* game, int depth, int original_depth);

#endif // MOVE_GENERATOR_H
