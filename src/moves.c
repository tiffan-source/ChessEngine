
#include "moves.h"

const char* move_type_to_string[14] = {
    "Quiet Move",
    "Double Pawn Push",
    "King Castle",
    "Queen Castle",
    "Capture",
    "En Passant Capture",
    "Knight Promotion",
    "Bishop Promotion",
    "Rook Promotion",
    "Queen Promotion",
    "Knight Promotion Capture",
    "Bishop Promotion Capture",
    "Rook Promotion Capture",
    "Queen Promotion Capture"
};

void print_move(Move move)
{
    Square from_square = GET_SOURCE_SQUARE_FROM_MOVE(move);
    Square to_square = GET_DESTINATION_SQUARE_FROM_MOVE(move);
    PieceType piece_type = GET_PIECE_TYPE_FROM_MOVE(move);
    MoveType move_type = GET_MOVE_TYPE_FROM_MOVE(move);

    printf("Details of move %d:\n", move);
    printf("From Square: %s\n", square_to_string[from_square]);
    printf("To Square: %s\n", square_to_string[to_square]);
    printf("Piece Type: %s\n", piece_type_to_string[piece_type]);
    printf("Move Type: %s\n", move_type_to_string[move_type]);
    printf("\n");
}

void print_move_as_uci(Move move)
{
    Square from_square = GET_SOURCE_SQUARE_FROM_MOVE(move);
    Square to_square = GET_DESTINATION_SQUARE_FROM_MOVE(move);
    char promotion_char = '\0';

    printf("%s%s", square_to_string[from_square], square_to_string[to_square]);

    switch (GET_MOVE_TYPE_FROM_MOVE(move))
    {
        case KNIGHT_PROMOTION:
        case KNIGHT_PROMOTION_CAPTURE:
            promotion_char = 'n';
            break;
        case BISHOP_PROMOTION:
        case BISHOP_PROMOTION_CAPTURE:
            promotion_char = 'b';
            break;
        case ROOK_PROMOTION:
        case ROOK_PROMOTION_CAPTURE:
            promotion_char = 'r';
            break;
        case QUEEN_PROMOTION:
        case QUEEN_PROMOTION_CAPTURE:
            promotion_char = 'q';
            break;
        default:
            /* code */
            break;
    }
    if (promotion_char != '\0')
    {
        printf("%c", promotion_char);
    }
}

void build_move_as_uci(Move move,char* result)
{
    Square from_square = GET_SOURCE_SQUARE_FROM_MOVE(move);
    Square to_square = GET_DESTINATION_SQUARE_FROM_MOVE(move);
    char promotion_char = '\0';

    // printf("%s%s", square_to_string[from_square], square_to_string[to_square]);

    switch (GET_MOVE_TYPE_FROM_MOVE(move))
    {
        case KNIGHT_PROMOTION:
        case KNIGHT_PROMOTION_CAPTURE:
            promotion_char = 'n';
            break;
        case BISHOP_PROMOTION:
        case BISHOP_PROMOTION_CAPTURE:
            promotion_char = 'b';
            break;
        case ROOK_PROMOTION:
        case ROOK_PROMOTION_CAPTURE:
            promotion_char = 'r';
            break;
        case QUEEN_PROMOTION:
        case QUEEN_PROMOTION_CAPTURE:
            promotion_char = 'q';
            break;
        default:
            /* code */
            break;
    }
    if (promotion_char != '\0')
    {
        // printf("%c", promotion_char);
    }

    snprintf(result, 6, "%s%s%c", square_to_string[from_square], square_to_string[to_square], promotion_char);
}

// This function makes a move and updates the Zobrist key accordingly


void promote_to_piece(Game* game, Move move, PieceType new_piece_type)
{
    Bitboard to_bitboard = pre_calculated_bit_shifts[GET_DESTINATION_SQUARE_FROM_MOVE(move)];
    Bitboard from_bitboard = pre_calculated_bit_shifts[GET_SOURCE_SQUARE_FROM_MOVE(move)];

    // First, remove the pawn from the source square
    if (GET_PIECE_TYPE_FROM_MOVE(move) == WHITE_PAWN) {
        game->white_pawns &= ~from_bitboard;
        game->zobrist_key ^= pawn_zobrist_magic_number[WHITE][GET_SOURCE_SQUARE_FROM_MOVE(move)];
    } else if (GET_PIECE_TYPE_FROM_MOVE(move) == BLACK_PAWN) {
        game->black_pawns &= ~from_bitboard;
        game->zobrist_key ^= pawn_zobrist_magic_number[BLACK][GET_SOURCE_SQUARE_FROM_MOVE(move)];
    }

    // Then, add the new piece to the destination square
    switch (new_piece_type) {
        case WHITE_QUEEN:
            game->white_queens |= to_bitboard;
            game->zobrist_key ^= queen_zobrist_magic_number[WHITE][GET_DESTINATION_SQUARE_FROM_MOVE(move)];
            break;
        case BLACK_QUEEN:
            game->black_queens |= to_bitboard;
            game->zobrist_key ^= queen_zobrist_magic_number[BLACK][GET_DESTINATION_SQUARE_FROM_MOVE(move)];
            break;
        case WHITE_ROOK:
            game->white_rooks |= to_bitboard;
            game->zobrist_key ^= rook_zobrist_magic_number[WHITE][GET_DESTINATION_SQUARE_FROM_MOVE(move)];
            break;
        case BLACK_ROOK:
            game->black_rooks |= to_bitboard;
            game->zobrist_key ^= rook_zobrist_magic_number[BLACK][GET_DESTINATION_SQUARE_FROM_MOVE(move)];
            break;
        case WHITE_BISHOP:
            game->white_bishops |= to_bitboard;
            game->zobrist_key ^= bishop_zobrist_magic_number[WHITE][GET_DESTINATION_SQUARE_FROM_MOVE(move)];
            break;
        case BLACK_BISHOP:
            game->black_bishops |= to_bitboard;
            game->zobrist_key ^= bishop_zobrist_magic_number[BLACK][GET_DESTINATION_SQUARE_FROM_MOVE(move)];
            break;
        case WHITE_KNIGHT:
            game->white_knights |= to_bitboard;
            game->zobrist_key ^= knight_zobrist_magic_number[WHITE][GET_DESTINATION_SQUARE_FROM_MOVE(move)];
            break;
        case BLACK_KNIGHT:
            game->black_knights |= to_bitboard;
            game->zobrist_key ^= knight_zobrist_magic_number[BLACK][GET_DESTINATION_SQUARE_FROM_MOVE(move)];
            break;
        default:
            break;
    }
}

void capture_piece_on_square(Game* game, Square square)
{
    Bitboard square_bitboard = pre_calculated_bit_shifts[square];
    
    if (game->turn == BLACK_TURN) {
        if (game->white_pawns & square_bitboard){
            game->white_pawns &= ~square_bitboard;
            game->zobrist_key ^= pawn_zobrist_magic_number[WHITE][square];
            return;
        }

        if (game->white_knights & square_bitboard){
            game->white_knights &= ~square_bitboard;
            game->zobrist_key ^= knight_zobrist_magic_number[WHITE][square];
            return;
        }

        if (game->white_bishops & square_bitboard){
            game->white_bishops &= ~square_bitboard;
            game->zobrist_key ^= bishop_zobrist_magic_number[WHITE][square];
            return;
        }

        if (game->white_rooks & square_bitboard){
            game->white_rooks &= ~square_bitboard;
            game->zobrist_key ^= rook_zobrist_magic_number[WHITE][square];
            if (square == A1){
                int previously = game->castling_rights;
                REVOK_CASTLING_RIGHT(game, WHITE_QUEEN_SIDE_CASTLING);
                game->zobrist_key ^= castling_rights_zobrist_magic_number[previously];
                game->zobrist_key ^= castling_rights_zobrist_magic_number[game->castling_rights];
            }
            else if (square == H1){
                int previously = game->castling_rights;
                REVOK_CASTLING_RIGHT(game, WHITE_KING_SIDE_CASTLING);
                game->zobrist_key ^= castling_rights_zobrist_magic_number[previously];
                game->zobrist_key ^= castling_rights_zobrist_magic_number[game->castling_rights];
            }
            
            return;
        }

        if (game->white_queens & square_bitboard){
            game->white_queens &= ~square_bitboard;
            game->zobrist_key ^= queen_zobrist_magic_number[WHITE][square];
            return;
        }

        if (game->white_king & square_bitboard){
            game->white_king &= ~square_bitboard;
            game->zobrist_key ^= king_zobrist_magic_number[WHITE][square];
            return;
        } 
    } else {
        if (game->black_pawns & square_bitboard){
            game->black_pawns &= ~square_bitboard;
            game->zobrist_key ^= pawn_zobrist_magic_number[BLACK][square];
            return;
        }

        if (game->black_knights & square_bitboard){
            game->black_knights &= ~square_bitboard;
            game->zobrist_key ^= knight_zobrist_magic_number[BLACK][square];
            return;
        }

        if (game->black_bishops & square_bitboard){
            game->black_bishops &= ~square_bitboard;
            game->zobrist_key ^= bishop_zobrist_magic_number[BLACK][square];
            return;
        }

        if (game->black_rooks & square_bitboard){
            game->black_rooks &= ~square_bitboard;
            game->zobrist_key ^= rook_zobrist_magic_number[BLACK][square];
            if (square == A8){
                int previously = game->castling_rights;
                REVOK_CASTLING_RIGHT(game, BLACK_QUEEN_SIDE_CASTLING);
                game->zobrist_key ^= castling_rights_zobrist_magic_number[previously];
                game->zobrist_key ^= castling_rights_zobrist_magic_number[game->castling_rights];
            }
            else if (square == H8){
                int previously = game->castling_rights;
                REVOK_CASTLING_RIGHT(game, BLACK_KING_SIDE_CASTLING);
                game->zobrist_key ^= castling_rights_zobrist_magic_number[previously];
                game->zobrist_key ^= castling_rights_zobrist_magic_number[game->castling_rights];
            }
            
            return;
        }

        if (game->black_queens & square_bitboard){
            game->black_queens &= ~square_bitboard;
            game->zobrist_key ^= queen_zobrist_magic_number[BLACK][square];
            return;
        }

        if (game->black_king & square_bitboard){
            game->black_king &= ~square_bitboard;
            game->zobrist_key ^= king_zobrist_magic_number[BLACK][square];
            return;
        } 
    }
}

void move_piece(Game* game, Move move)
{
    int previously;
    Square source_square = GET_SOURCE_SQUARE_FROM_MOVE(move);
    Square destination_square = GET_DESTINATION_SQUARE_FROM_MOVE(move);
    Bitboard from_bitboard = pre_calculated_bit_shifts[source_square];
    Bitboard to_bitboard = pre_calculated_bit_shifts[destination_square];

    switch (GET_PIECE_TYPE_FROM_MOVE(move)) {
        case WHITE_PAWN:
            game->white_pawns &= ~from_bitboard;
            game->zobrist_key ^= pawn_zobrist_magic_number[WHITE][source_square];

            game->white_pawns |= to_bitboard;
            game->zobrist_key ^= pawn_zobrist_magic_number[WHITE][destination_square];
            break;
        case BLACK_PAWN:
            game->black_pawns &= ~from_bitboard;
            game->zobrist_key ^= pawn_zobrist_magic_number[BLACK][source_square];

            game->black_pawns |= to_bitboard;
            game->zobrist_key ^= pawn_zobrist_magic_number[BLACK][destination_square];
            break;
        case WHITE_KNIGHT:
            game->white_knights &= ~from_bitboard;
            game->zobrist_key ^= knight_zobrist_magic_number[WHITE][source_square];
            game->white_knights |= to_bitboard;
            game->zobrist_key ^= knight_zobrist_magic_number[WHITE][destination_square];
            break;
        case BLACK_KNIGHT:
            game->black_knights &= ~from_bitboard;
            game->zobrist_key ^= knight_zobrist_magic_number[BLACK][source_square];
            game->black_knights |= to_bitboard;
            game->zobrist_key ^= knight_zobrist_magic_number[BLACK][destination_square];
            break;
        case WHITE_BISHOP:
            game->white_bishops &= ~from_bitboard;
            game->zobrist_key ^= bishop_zobrist_magic_number[WHITE][source_square];
            game->white_bishops |= to_bitboard;
            game->zobrist_key ^= bishop_zobrist_magic_number[WHITE][destination_square];
            break;
        case BLACK_BISHOP:  
            game->black_bishops &= ~from_bitboard;
            game->zobrist_key ^= bishop_zobrist_magic_number[BLACK][source_square];
            game->black_bishops |= to_bitboard;
            game->zobrist_key ^= bishop_zobrist_magic_number[BLACK][destination_square];
            break;
        case WHITE_ROOK:
            game->white_rooks &= ~from_bitboard;
            game->zobrist_key ^= rook_zobrist_magic_number[WHITE][source_square];
            game->white_rooks |= to_bitboard;
            game->zobrist_key ^= rook_zobrist_magic_number[WHITE][destination_square];
            if(source_square == A1){
                int previously = game->castling_rights;
                REVOK_CASTLING_RIGHT(game, WHITE_QUEEN_SIDE_CASTLING);
                game->zobrist_key ^= castling_rights_zobrist_magic_number[previously];
                game->zobrist_key ^= castling_rights_zobrist_magic_number[game->castling_rights];
            }
            else if(source_square == H1){
                int previously = game->castling_rights;
                REVOK_CASTLING_RIGHT(game, WHITE_KING_SIDE_CASTLING);
                game->zobrist_key ^= castling_rights_zobrist_magic_number[previously];
                game->zobrist_key ^= castling_rights_zobrist_magic_number[game->castling_rights];
            }
            break;
        case BLACK_ROOK:
            game->black_rooks &= ~from_bitboard;
            game->zobrist_key ^= rook_zobrist_magic_number[BLACK][source_square];
            game->black_rooks |= to_bitboard;
            game->zobrist_key ^= rook_zobrist_magic_number[BLACK][destination_square];
            if(source_square == A8){
                int previously = game->castling_rights;
                REVOK_CASTLING_RIGHT(game, BLACK_QUEEN_SIDE_CASTLING);
                game->zobrist_key ^= castling_rights_zobrist_magic_number[previously];
                game->zobrist_key ^= castling_rights_zobrist_magic_number[game->castling_rights];
            }
            else if(source_square == H8){
                int previously = game->castling_rights;
                REVOK_CASTLING_RIGHT(game, BLACK_KING_SIDE_CASTLING);
                game->zobrist_key ^= castling_rights_zobrist_magic_number[previously];
                game->zobrist_key ^= castling_rights_zobrist_magic_number[game->castling_rights];
            }
            break;
        case WHITE_QUEEN:
            game->white_queens &= ~from_bitboard;
            game->zobrist_key ^= queen_zobrist_magic_number[WHITE][source_square];
            game->white_queens |= to_bitboard;
            game->zobrist_key ^= queen_zobrist_magic_number[WHITE][destination_square];
            break;
        case BLACK_QUEEN:
            game->black_queens &= ~from_bitboard;
            game->zobrist_key ^= queen_zobrist_magic_number[BLACK][source_square];
            game->black_queens |= to_bitboard;
            game->zobrist_key ^= queen_zobrist_magic_number[BLACK][destination_square];
            break;
        case WHITE_KING:
            game->white_king &= ~from_bitboard;
            game->zobrist_key ^= king_zobrist_magic_number[WHITE][source_square];
            game->white_king |= to_bitboard;
            game->zobrist_key ^= king_zobrist_magic_number[WHITE][destination_square];
            previously = game->castling_rights;
            REVOK_CASTLING_RIGHT(game, WHITE_KING_SIDE_CASTLING | WHITE_QUEEN_SIDE_CASTLING);
            game->zobrist_key ^= castling_rights_zobrist_magic_number[previously];
            game->zobrist_key ^= castling_rights_zobrist_magic_number[game->castling_rights];
            break;
        case BLACK_KING:
            game->black_king &= ~from_bitboard;
            game->zobrist_key ^= king_zobrist_magic_number[BLACK][source_square];
            game->black_king |= to_bitboard;
            game->zobrist_key ^= king_zobrist_magic_number[BLACK][destination_square];
            previously = game->castling_rights;
            REVOK_CASTLING_RIGHT(game, BLACK_KING_SIDE_CASTLING | BLACK_QUEEN_SIDE_CASTLING);
            game->zobrist_key ^= castling_rights_zobrist_magic_number[previously];
            game->zobrist_key ^= castling_rights_zobrist_magic_number[game->castling_rights];
            break;
        // Add cases for other piece types as needed
        default:
            break;
    }
}

void make_move(Game* game, Move move)
{
    int previous_en_passant_square = game->en_passant_target_square;

    switch (GET_MOVE_TYPE_FROM_MOVE(move)) {
        case CAPTURE:
            move_piece(game, move);
            capture_piece_on_square(game, GET_DESTINATION_SQUARE_FROM_MOVE(move));
            break;

        case EN_PASSANT_CAPTURE:
            move_piece(game, move);
            {
                int ep_square = (game->turn == WHITE_TURN) ? GET_DESTINATION_SQUARE_FROM_MOVE(move) + 8 : GET_DESTINATION_SQUARE_FROM_MOVE(move) - 8;
                capture_piece_on_square(game, ep_square);
            }
            break;
        
        case QUIET_MOVES:
        case DOUBLE_PAWN_PUSH:
            move_piece(game, move);
            break;

        case QUEEN_PROMOTION:
            promote_to_piece(game, move, (game->turn == WHITE_TURN) ? WHITE_QUEEN : BLACK_QUEEN);
            break;

        case ROOK_PROMOTION:
            promote_to_piece(game, move, (game->turn == WHITE_TURN) ? WHITE_ROOK : BLACK_ROOK);
            break;

        case BISHOP_PROMOTION:
            promote_to_piece(game, move, (game->turn == WHITE_TURN) ? WHITE_BISHOP : BLACK_BISHOP);
            break;

        case KNIGHT_PROMOTION:
            promote_to_piece(game, move, (game->turn == WHITE_TURN) ? WHITE_KNIGHT : BLACK_KNIGHT);
            break;


        case QUEEN_PROMOTION_CAPTURE:
            capture_piece_on_square(game, GET_DESTINATION_SQUARE_FROM_MOVE(move));
            promote_to_piece(game, move, (game->turn == WHITE_TURN) ? WHITE_QUEEN : BLACK_QUEEN);
            break;

        case KNIGHT_PROMOTION_CAPTURE:
            capture_piece_on_square(game, GET_DESTINATION_SQUARE_FROM_MOVE(move));
            promote_to_piece(game, move, (game->turn == WHITE_TURN) ? WHITE_KNIGHT : BLACK_KNIGHT);
            break;

        case BISHOP_PROMOTION_CAPTURE:
            capture_piece_on_square(game, GET_DESTINATION_SQUARE_FROM_MOVE(move));
            promote_to_piece(game, move, (game->turn == WHITE_TURN) ? WHITE_BISHOP: BLACK_BISHOP);
            break;

        case ROOK_PROMOTION_CAPTURE:
            capture_piece_on_square(game, GET_DESTINATION_SQUARE_FROM_MOVE(move));
            promote_to_piece(game, move, (game->turn == WHITE_TURN) ? WHITE_ROOK : BLACK_ROOK);
            break;

        case KING_CASTLE:
            move_piece(game, move);
            if(game->turn == WHITE_TURN){
                move_piece(game, CREATE_MOVE(H1, F1, WHITE_ROOK, QUIET_MOVES));
            }
            else{
                move_piece(game, CREATE_MOVE(H8, F8, BLACK_ROOK, QUIET_MOVES));
            }
            break;

        case QUEEN_CASTLE:
            move_piece(game, move);
            if(game->turn == WHITE_TURN){
                move_piece(game, CREATE_MOVE(A1, D1, WHITE_ROOK, QUIET_MOVES));
            }
            else{
                move_piece(game, CREATE_MOVE(A8, D8, BLACK_ROOK, QUIET_MOVES));  
            }
            break;
    }

    if (GET_MOVE_TYPE_FROM_MOVE(move) == DOUBLE_PAWN_PUSH)
    {
        game->en_passant_target_square = GET_DESTINATION_SQUARE_FROM_MOVE(move) + ((GET_PIECE_TYPE_FROM_MOVE(move) == WHITE_PAWN) ? 8 : -8);
        game->zobrist_key ^= en_passant_square_zobrist_magic_number[game->en_passant_target_square];
        if (previous_en_passant_square != -1) {
            game->zobrist_key ^= en_passant_square_zobrist_magic_number[previous_en_passant_square];
        }
    }
    else
    {
        game->en_passant_target_square = -1; // No en passant target
        if (previous_en_passant_square != -1) {
            game->zobrist_key ^= en_passant_square_zobrist_magic_number[previous_en_passant_square];
        }
    }
    
    game->turn = !game->turn; // Switch turn
    game->zobrist_key ^= black_to_move_zobrist_magic_number;
}