
#include "zobrist_key.h"

ZobristKey pawn_zobrist_magic_number[2][64];
ZobristKey knight_zobrist_magic_number[2][64];
ZobristKey bishop_zobrist_magic_number[2][64];
ZobristKey rook_zobrist_magic_number[2][64];
ZobristKey queen_zobrist_magic_number[2][64];
ZobristKey king_zobrist_magic_number[2][64];
ZobristKey black_to_move_zobrist_magic_number;
ZobristKey castling_rights_zobrist_magic_number[16];
ZobristKey en_passant_square_zobrist_magic_number[64];

void initialize_magic_zobrist_numbers() {
    srand(256);

    black_to_move_zobrist_magic_number = RANDOM_U64_FEWBITS();

    for (int square = 0; square < 64; square++)
    {
        for (int side = 0; side < 2; side++)
        {
            pawn_zobrist_magic_number[side][square] = RANDOM_U64_FEWBITS();
            knight_zobrist_magic_number[side][square] = RANDOM_U64_FEWBITS();
            bishop_zobrist_magic_number[side][square] = RANDOM_U64_FEWBITS();
            rook_zobrist_magic_number[side][square] = RANDOM_U64_FEWBITS();
            queen_zobrist_magic_number[side][square] = RANDOM_U64_FEWBITS();
            king_zobrist_magic_number[side][square] = RANDOM_U64_FEWBITS(); 
        }
        en_passant_square_zobrist_magic_number[square] = RANDOM_U64_FEWBITS();
    }

    for (int i = 0; i < 16; i++)
    {
        castling_rights_zobrist_magic_number[i] = RANDOM_U64_FEWBITS();
    }
}
