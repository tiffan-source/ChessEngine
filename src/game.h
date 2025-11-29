
#ifndef GAME_H
#define GAME_H

#include "board.h"

#define BLACK_OCCUPENCY(game) (game->black_pawns | game->black_knights | game->black_bishops | game->black_rooks | game->black_queens | game->black_king)
#define WHITE_OCCUPENCY(game) (game->white_pawns | game->white_knights | game->white_bishops | game->white_rooks | game->white_queens | game->white_king)
#define ALL_OCCUPENCY(game) (BLACK_OCCUPENCY(game) | WHITE_OCCUPENCY(game))
#define REVOK_CASTLING_RIGHT(game, rights) (game->castling_rights &= ~(rights))

typedef enum TURN {
    BLACK_TURN,
    WHITE_TURN
}TURN;

enum CASTLING_RIGHTS {
    WHITE_KING_SIDE_CASTLING = 8,
    WHITE_QUEEN_SIDE_CASTLING = 4,
    BLACK_KING_SIDE_CASTLING = 2,
    BLACK_QUEEN_SIDE_CASTLING = 1
};

typedef struct Game{
    Bitboard black_pawns;
    Bitboard black_knights;
    Bitboard black_bishops;
    Bitboard black_rooks;
    Bitboard black_queens;
    Bitboard black_king;
    
    Bitboard white_pawns;
    Bitboard white_knights;
    Bitboard white_bishops;
    Bitboard white_rooks;
    Bitboard white_queens;
    Bitboard white_king;

    TURN turn;
    int castling_rights;
    int en_passant_target_square;
} Game;

Game* create_game();
Game* create_game_from_FEN(char* FEN);

void print_representation_of_chess_game(Game* game);

void free_game(Game* game);

#endif // GAME_H
