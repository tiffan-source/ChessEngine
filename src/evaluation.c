
#include "evaluation.h"

int pawn_square_table[64] = {
    60, 60, 60, 60, 60, 60, 60, 60,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
     5,  5, 10, 25, 25, 10,  5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5, -5,-10,  0,  0,-10, -5,  5,
     5, 10, 10,-20,-20, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0
};

int knight_square_table[64] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
};

int bishop_square_table[64] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
};

int rook_square_table[64] = {
    5, 10, 10, 10, 10, 10, 10,  5,
    15, 20, 20, 20, 20, 20, 20, 15,
     0,  5,  5,  5,  5,  5,  5,  0,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     0,  0,  0,  5,  5,  0,  0,  0
};

int king_square_table[64] = {
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    20, 20,  0,  0,  0,  0, 20, 20,
    20, 30, 10,  0,  0, 10, 30, 20
};

int material_evaluation_for_side(Game* game)
{
    int pawn_advantage = COUNT_BITS_SET(game->white_pawns) - COUNT_BITS_SET(game->black_pawns);
    int knight_advantage = COUNT_BITS_SET(game->white_knights) - COUNT_BITS_SET(game->black_knights);
    int bishop_advantage = COUNT_BITS_SET(game->white_bishops) - COUNT_BITS_SET(game->black_bishops);
    int rook_advantage = COUNT_BITS_SET(game->white_rooks) - COUNT_BITS_SET(game->black_rooks);
    int queen_advantage = COUNT_BITS_SET(game->white_queens) - COUNT_BITS_SET(game->black_queens);
    return (100 * pawn_advantage + 300 * knight_advantage + 350 * bishop_advantage + 400 * rook_advantage + 900 * queen_advantage) * (game->turn == WHITE_TURN ? 1 : -1);
}

int material_evaluation_with_piece_square_table_for_side(Game* game)
{
    int score = 0;
    Bitboard pawns = game->white_pawns;
    while (pawns) {
        int square = GET_LSB_INDEX(pawns);
        score += pawn_square_table[square] + 100;
        pawns = CLEAR_BIT_ON_BITBOARD(pawns, square);
    }
    pawns = game->black_pawns;
    while (pawns) {
        int square = GET_LSB_INDEX(pawns);
        score -= pawn_square_table[square ^ 56] + 100;
        pawns = CLEAR_BIT_ON_BITBOARD(pawns, square);
    }

    Bitboard knights = game->white_knights;
    while (knights) {
        int square = GET_LSB_INDEX(knights);
        score += knight_square_table[square] + 300;
        knights = CLEAR_BIT_ON_BITBOARD(knights, square);
    }
    knights = game->black_knights;
    while (knights) {
        int square = GET_LSB_INDEX(knights);
        score -= knight_square_table[square ^ 56] + 300;
        knights = CLEAR_BIT_ON_BITBOARD(knights, square);
    }

    Bitboard bishops = game->white_bishops;
    while (bishops) {
        int square = GET_LSB_INDEX(bishops);
        score += bishop_square_table[square] + 350;
        bishops = CLEAR_BIT_ON_BITBOARD(bishops, square);
    }
    bishops = game->black_bishops;
    while (bishops) {
        int square = GET_LSB_INDEX(bishops);
        score -= bishop_square_table[square ^ 56] + 350;
        bishops = CLEAR_BIT_ON_BITBOARD(bishops, square);
    }

    Bitboard rooks = game->white_rooks;
    while (rooks) {
        int square = GET_LSB_INDEX(rooks);
        score += rook_square_table[square] + 400;
        rooks = CLEAR_BIT_ON_BITBOARD(rooks, square);
    }
    rooks = game->black_rooks;
    while (rooks) {
        int square = GET_LSB_INDEX(rooks);
        score -= rook_square_table[square ^ 56] + 400;
        rooks = CLEAR_BIT_ON_BITBOARD(rooks, square);
    }

    Bitboard kings = game->white_king;
    while (kings) {
        int square = GET_LSB_INDEX(kings);
        score += king_square_table[square];
        kings =CLEAR_BIT_ON_BITBOARD(kings, square);
    }
    kings = game->black_king;
    while (kings) {
        int square = GET_LSB_INDEX(kings);
        score -= king_square_table[square ^ 56];
        kings = CLEAR_BIT_ON_BITBOARD(kings, square);
    }

    score += (COUNT_BITS_SET(game->white_queens) - COUNT_BITS_SET(game->black_queens))* 900;

    return score * (game->turn == WHITE_TURN ? 1 : -1);
}

int is_a_mate_score(int score)
{
    return (score <= MIN + 100) || (score >= MAX - 100);
}