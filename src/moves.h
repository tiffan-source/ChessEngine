
#ifndef MOVES_H
#define MOVES_H

#include "pieces.h"
#include "game.h"
#include "zobrist_key.h"

/**
 * To represent a chess move inside our engine we need to encode the following information:
 * - The starting square of the piece being moved : 6 bits (0-63)
 * - The destination square of the piece being moved : 6 bits (0-63)
 * - The type of piece being moved : 4 bits (0-11)
 * - The type of move being made : 4 bits (0-15)
 * 
 * So we need an integer type that can hold at least 20 bits of information.
 */


#define SOURCE_SQUARE_MASK      0x3F          // 6 bits for source square
#define DESTINATION_SQUARE_MASK 0xFC0         // 6 bits for destination square
#define PIECE_TYPE_MASK         0xF000        // 4 bits for piece type
#define MOVE_TYPE_MASK          0xF0000       // 4 bits for move type

// Macros to extract components from a move
#define GET_SOURCE_SQUARE(scored_move)      ((scored_move.move) & SOURCE_SQUARE_MASK)
#define GET_DESTINATION_SQUARE(scored_move) (((scored_move.move) & DESTINATION_SQUARE_MASK) >> 6)
#define GET_PIECE_TYPE(scored_move)         (((scored_move.move) & PIECE_TYPE_MASK) >> 12)
#define GET_MOVE_TYPE(scored_move)          (((scored_move.move) & MOVE_TYPE_MASK) >> 16)

#define GET_SOURCE_SQUARE_FROM_MOVE(move)      ((move) & SOURCE_SQUARE_MASK)
#define GET_DESTINATION_SQUARE_FROM_MOVE(move) (((move) & DESTINATION_SQUARE_MASK) >> 6)
#define GET_PIECE_TYPE_FROM_MOVE(move)         (((move) & PIECE_TYPE_MASK) >> 12)
#define GET_MOVE_TYPE_FROM_MOVE(move)          (((move) & MOVE_TYPE_MASK) >> 16)

#define CREATE_MOVE(from_square, to_square, piece_type, move_type) \
    ( (Move)( (((from_square) & 0x3FULL)                         ) \
           | ((((to_square)   & 0x3FULL) << 6)                    ) \
           | ((((piece_type)  & 0xFULL)  << 12)                   ) \
           | ((((move_type)   & 0xFULL)  << 16)                   ) ) )

      
#define CREATE_SCORED_MOVE(from_square, to_square, piece_type, move_type) \
        ( (ScoredMove){ .score = (0), .move = CREATE_MOVE(from_square, to_square, piece_type, move_type) } )

typedef unsigned int Move;

typedef struct ScoredMove {
    long int score;
    long int ordering_score;
    Move move;
} ScoredMove;

typedef struct MoveList {
    ScoredMove moves[256];
    int current_index;
} MoveList;

typedef enum MoveType {
    QUIET_MOVES,
    DOUBLE_PAWN_PUSH,
    KING_CASTLE,
    QUEEN_CASTLE,
    CAPTURE,
    EN_PASSANT_CAPTURE,
    KNIGHT_PROMOTION,
    BISHOP_PROMOTION,
    ROOK_PROMOTION,
    QUEEN_PROMOTION,
    KNIGHT_PROMOTION_CAPTURE,
    BISHOP_PROMOTION_CAPTURE,
    ROOK_PROMOTION_CAPTURE,
    QUEEN_PROMOTION_CAPTURE
}MoveType;

extern const char* move_type_to_string[14];

// Function to create a move from its components
void print_move(Move move);
void print_move_as_uci(Move move);
void build_move_as_uci(Move move,char* result);

void make_move(Game* game, Move move);
void make_null_move(Game* game);

#endif // MOVES_H
