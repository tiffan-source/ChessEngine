
#include "evaluation.h"

int material_evaluation(Game* game)
{
    int pawn_advantage = count_bits_set(game->white_pawns) - count_bits_set(game->black_pawns);
    int knight_advantage = count_bits_set(game->white_knights) - count_bits_set(game->black_knights);
    int bishop_advantage = count_bits_set(game->white_bishops) - count_bits_set(game->black_bishops);
    int rook_advantage = count_bits_set(game->white_rooks) - count_bits_set(game->black_rooks);
    int queen_advantage = count_bits_set(game->white_queens) - count_bits_set(game->black_queens);
    return pawn_advantage + 3* knight_advantage + 3* bishop_advantage + 4* rook_advantage + 9* queen_advantage;
}