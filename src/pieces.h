
#ifndef PIECES_H
#define PIECES_H

typedef enum PieceType {
    BLACK_PAWN,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_ROOK,
    BLACK_QUEEN,
    BLACK_KING,
    WHITE_PAWN,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_ROOK,
    WHITE_QUEEN,
    WHITE_KING
} PieceType;

extern const char* piece_type_to_string[12];

#endif // PIECES_H
