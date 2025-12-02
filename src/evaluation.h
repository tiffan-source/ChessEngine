
#ifndef EVALUATION_H
#define EVALUATION_H

#include "game.h"
#include "binary_tools.h"
#include "moves.h"
#include "king_moves.h"
#include "move_generator.h"
#include "standard_lib.h"

int is_king_mate(Game* board_state);
int material_evaluation(Game* game);

#endif // EVALUATION_H
