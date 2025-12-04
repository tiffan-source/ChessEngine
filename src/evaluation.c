
#include "evaluation.h"

int material_evaluation(Game* game)
{
    int pawn_advantage = COUNT_BITS_SET(game->white_pawns) - COUNT_BITS_SET(game->black_pawns);
    int knight_advantage = COUNT_BITS_SET(game->white_knights) - COUNT_BITS_SET(game->black_knights);
    int bishop_advantage = COUNT_BITS_SET(game->white_bishops) - COUNT_BITS_SET(game->black_bishops);
    int rook_advantage = COUNT_BITS_SET(game->white_rooks) - COUNT_BITS_SET(game->black_rooks);
    int queen_advantage = COUNT_BITS_SET(game->white_queens) - COUNT_BITS_SET(game->black_queens);
    return pawn_advantage + 3* knight_advantage + 3* bishop_advantage + 4* rook_advantage + 9* queen_advantage;
}

int material_evaluation_for_side(Game* game)
{
    int pawn_advantage = COUNT_BITS_SET(game->white_pawns) - COUNT_BITS_SET(game->black_pawns);
    int knight_advantage = COUNT_BITS_SET(game->white_knights) - COUNT_BITS_SET(game->black_knights);
    int bishop_advantage = COUNT_BITS_SET(game->white_bishops) - COUNT_BITS_SET(game->black_bishops);
    int rook_advantage = COUNT_BITS_SET(game->white_rooks) - COUNT_BITS_SET(game->black_rooks);
    int queen_advantage = COUNT_BITS_SET(game->white_queens) - COUNT_BITS_SET(game->black_queens);
    return (pawn_advantage + 3* knight_advantage + 3* bishop_advantage + 4* rook_advantage + 9* queen_advantage) * (game->turn == WHITE_TURN ? 1 : -1);
}
