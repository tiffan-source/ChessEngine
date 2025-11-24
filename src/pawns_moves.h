
#ifndef PAWNS_MOVES_H
#define PAWNS_MOVES_H

#include "board.h"

Bitboard generate_pawns_quiet_moves_from_square(Side side, Square square);
Bitboard generate_pawns_capture_moves_from_square(Side side, Square square);

#endif // PAWNS_MOVES_H
