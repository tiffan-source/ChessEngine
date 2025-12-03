
#ifndef BOARD_H
#define BOARD_H

#include "binary_tools.h"

#define RANK_8 0xFFULL
#define RANK_7 0xFF00ULL
#define RANK_1 0xFF00000000000000ULL
#define RANK_2 0xFF000000000000ULL

#define FILE_A 0x0101010101010101ULL
#define FILE_H 0x8080808080808080ULL
#define FILE_B 0x0202020202020202ULL
#define FILE_G 0x4040404040404040ULL

#define CHESS_BOARDER 0xFF818181818181FFULL

#define SET_BIT_ON_BITBOARD(bitboard, square) ((bitboard) | (1ULL << (square)))

#define CLEAR_BIT_ON_BITBOARD(bitboard, square) \
    ((bitboard) & ~(1ULL << (square)))

#define BIT_ON_BITBOARD_HIT_8_RANK(bitboard) \
    (((bitboard) & RANK_8) ? 1 : 0)

#define BIT_ON_BITBOARD_HIT_7_RANK(bitboard) \
    (((bitboard) & RANK_7) ? 1 : 0)

#define BIT_ON_BITBOARD_HIT_1_RANK(bitboard) \
    (((bitboard) & RANK_1) ? 1 : 0)

#define BIT_ON_BITBOARD_HIT_2_RANK(bitboard) \
    (((bitboard) & RANK_2) ? 1 : 0)

#define BIT_ON_BITBOARD_HIT_A_FILE(bitboard) \
    (((bitboard) & FILE_A) ? 1 : 0)

#define BIT_ON_BITBOARD_HIT_B_FILE(bitboard) \
    (((bitboard) & FILE_B) ? 1 : 0)

#define BIT_ON_BITBOARD_HIT_H_FILE(bitboard) \
    (((bitboard) & FILE_H) ? 1 : 0)

#define BIT_ON_BITBOARD_HIT_G_FILE(bitboard) \
    (((bitboard) & FILE_G) ? 1 : 0)

typedef U64 Bitboard;

typedef enum Square {
    A8, B8, C8, D8, E8, F8, G8, H8,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A1, B1, C1, D1, E1, F1, G1, H1
}Square;

extern const char* square_to_string[64];

typedef enum Side {
    BLACK = 0,
    WHITE = 1
}Side;

char* string_bitboard_on_chess_board(Bitboard position);


#endif // BOARD_H
