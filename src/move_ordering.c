
#include "move_ordering.h"

// score_mvv_lva[Attacker][Victime]

const int score_mvv_lva[6][6] = {
    //Victime Pawn  Knight Bishop Rook Queen King
    //Attacker
    //Pawn          
              {106, 206,   306,   406, 506,  606},
    //Knight          
              {105, 205,   305,   405, 505,  605},
    //Bishop          
              {104, 204,   304,   404, 504,  604},
    //Rook          
              {103, 203,   303,   403, 503,  603},
    //Queen          
              {102, 202,   302,   402, 502,  602},
    //King          
              {101, 201,   301,   401, 501,  601},
};


// killer_move[ply][index]
Move killer_move[MAX_DEPTH][2] = {0};

void add_killer_move_at_ply(Move move, int ply)
{
    killer_move[ply][1] = killer_move[ply][0];
    killer_move[ply][0] = move;
}

PieceType check_victime_piece_on_square(Game* game, Square square)
{
    Bitboard square_bitboard = pre_calculated_bit_shifts[square];
    
    if (game->turn == BLACK_TURN) {
        if (game->white_pawns & square_bitboard){
            return WHITE_PAWN;
        }

        if (game->white_knights & square_bitboard){
            return WHITE_KNIGHT;
        }

        if (game->white_bishops & square_bitboard){
            return WHITE_BISHOP;
        }

        if (game->white_rooks & square_bitboard){
            return WHITE_ROOK;
        }

        if (game->white_queens & square_bitboard){
            return WHITE_QUEEN;
        }

        if (game->white_king & square_bitboard){
            return WHITE_KING;
        } 
    } else {
        if (game->black_pawns & square_bitboard){
            return BLACK_PAWN;
        }

        if (game->black_knights & square_bitboard){
            return BLACK_KNIGHT;
        }

        if (game->black_bishops & square_bitboard){
            return BLACK_BISHOP;
        }

        if (game->black_rooks & square_bitboard){            
            return BLACK_ROOK;
        }

        if (game->black_queens & square_bitboard){
            return BLACK_QUEEN;
        }

        if (game->black_king & square_bitboard){
            return BLACK_KING;
        } 
    }
}


void scored_move_using(Game* game, ScoredMove* scored_move, int ply)
{
    switch (GET_MOVE_TYPE_FROM_MOVE(scored_move->move))
    {
    case CAPTURE:
    case ROOK_PROMOTION_CAPTURE:
    case QUEEN_PROMOTION_CAPTURE:
    case KNIGHT_PROMOTION_CAPTURE:
    case BISHOP_PROMOTION_CAPTURE:
        scored_move->score = score_mvv_lva[
            GET_PIECE_TYPE((*scored_move)) % 6
        ][
            check_victime_piece_on_square(game, GET_DESTINATION_SQUARE((*scored_move))) % 6
        ];
        break;
    
    default:
        if (scored_move->move == killer_move[ply][0])
            scored_move->score = 100;
        else if(scored_move->move == killer_move[ply][1])
            scored_move->score = 90;
        break;
    }
}

int compare_scored_move(const void *a, const void *b) {
    unsigned int ia = (*(const ScoredMove*)a).score;
    unsigned int ib = (*(const ScoredMove*)b).score;
    return ib - ia;
}

void order_move(Game* game, MoveList* move_list, int ply)
{
    for (int i = 0; i < move_list->current_index; i++)
    {
        scored_move_using(game, move_list->moves + i, ply);
    }
    
    qsort(move_list->moves, move_list->current_index, sizeof(ScoredMove), compare_scored_move);
}