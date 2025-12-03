
#include "game.h"

Game* create_game()
{
    Game* game = (Game*)malloc(sizeof(Game));

    game->black_pawns = 0xFF00ULL;
    game->black_knights = 0x42ULL;
    game->black_bishops = 0x24ULL;
    game->black_rooks = 0x81ULL;
    game->black_queens = 0x8ULL;
    game->black_king = 0x10ULL;

    game->white_pawns = 0xFF000000000000ULL;
    game->white_knights = 0x4200000000000000ULL;
    game->white_bishops = 0x2400000000000000ULL;
    game->white_rooks = 0x8100000000000000ULL;
    game->white_queens = 0x800000000000000ULL;
    game->white_king = 0x1000000000000000ULL;

    game->turn = WHITE_TURN;
    game->castling_rights = ALL_CASTLING_RIGHTS;
    game->en_passant_target_square = -1;
    return game;
}

Game* create_game_from_FEN(char* FEN)
{
    int i = 0;
    int rank = 8;
    int file = 0;
    int empty_squares;


    Game* game = (Game*)malloc(sizeof(Game));
    game->black_pawns = 0ULL;
    game->black_knights = 0ULL;
    game->black_bishops = 0ULL;
    game->black_rooks = 0ULL;
    game->black_queens = 0ULL;
    game->black_king = 0ULL;
    game->white_pawns = 0ULL;
    game->white_knights = 0ULL;
    game->white_bishops = 0ULL;
    game->white_rooks = 0ULL;
    game->white_queens = 0ULL;
    game->white_king = 0ULL;

    while(*(FEN + i) != ' ')
    {
        if (*(FEN + i) == '/')
        {
            rank--;
            file = 0;
            i++;
            continue;
        }

        if(*(FEN + i) >= '1' && *(FEN + i) <= '8')
        {
            empty_squares = *(FEN + i) - '0';
            file += empty_squares;
            i++;
            continue;
        }

        switch (*(FEN + i))
        {
            case 'p':
                game->black_pawns = SET_BIT_ON_BITBOARD(game->black_pawns, (Square)((8 - rank) * 8 + file));
                break;

            case 'r':
                game->black_rooks = SET_BIT_ON_BITBOARD(game->black_rooks, (Square)((8 - rank) * 8 + file));
                break;

            case 'n':
                game->black_knights = SET_BIT_ON_BITBOARD(game->black_knights, (Square)((8 - rank) * 8 + file));
                break;

            case 'b':
                game->black_bishops = SET_BIT_ON_BITBOARD(game->black_bishops, (Square)((8 - rank) * 8 + file));
                break;

            case 'q':
                game->black_queens = SET_BIT_ON_BITBOARD(game->black_queens, (Square)((8 - rank) * 8 + file));
                break;

            case 'k':
                game->black_king = SET_BIT_ON_BITBOARD(game->black_king, (Square)((8 - rank) * 8 + file));
                break;

            case 'P':
                game->white_pawns = SET_BIT_ON_BITBOARD(game->white_pawns, (Square)((8 - rank) * 8 + file));
                break;

            case 'R':
                game->white_rooks = SET_BIT_ON_BITBOARD(game->white_rooks, (Square)((8 - rank) * 8 + file));
                break;

            case 'N':
                game->white_knights = SET_BIT_ON_BITBOARD(game->white_knights, (Square)((8 - rank) * 8 + file));
                break;

            case 'B':
                game->white_bishops = SET_BIT_ON_BITBOARD(game->white_bishops, (Square)((8 - rank) * 8 + file));
                break;

            case 'Q':
                game->white_queens = SET_BIT_ON_BITBOARD(game->white_queens, (Square)((8 - rank) * 8 + file));
                break;

            case 'K':
                game->white_king = SET_BIT_ON_BITBOARD(game->white_king, (Square)((8 - rank) * 8 + file));
                break;

            default:
                break;
        }

        file++;
        i++;
    }

    i++; // skip space

    if (*(FEN + i) == 'w')
    {
        game->turn = WHITE_TURN;
    }
    else if (*(FEN + i) == 'b')
    {
        game->turn = BLACK_TURN;
    }

    i+= 2;

    game->castling_rights = 0;
    while(*(FEN + i) != ' ')
    {
        switch (*(FEN + i))
        {
            case 'K':
                game->castling_rights += WHITE_KING_SIDE_CASTLING;
                break;

            case 'Q':
                game->castling_rights += WHITE_QUEEN_SIDE_CASTLING;
                break;

            case 'k':
                game->castling_rights += BLACK_KING_SIDE_CASTLING;
                break;

            case 'q':
                game->castling_rights += BLACK_QUEEN_SIDE_CASTLING;
                break;

            case '-':
                game->castling_rights = 0;
                break;

            default:
                break;
        }
        i++;
    }

    i++; // skip space

    if (*(FEN + i) == '-')
    {
        game->en_passant_target_square = -1;
    }
    else
    {
        file = *(FEN + i) - 'a';
        rank = *(FEN + i + 1) - '0';
        game->en_passant_target_square = (8 - rank) * 8 + file;
    }

    return game;
}

void free_game(Game* game)
{
    free(game);
}

void print_representation_of_chess_game(Game* game)
{
    int index;

    for (int i = 0; i <= 7; i++)
    {
        printf("%c ", '8' - i);

        for (int j = 1; j <= 8; j++)
        {
            index = (i * 8 + (j - 1));
            if (game->black_pawns & pre_calculated_bit_shifts[index])
                printf("♟%c", (j == 8) ? '\n' : ' ');
            else if (game->black_rooks & pre_calculated_bit_shifts[index])
                printf("♜%c", (j == 8) ? '\n' : ' ');
            else if (game->black_knights & pre_calculated_bit_shifts[index])
                printf("♞%c", (j == 8) ? '\n' : ' ');
            else if (game->black_bishops & pre_calculated_bit_shifts[index])
                printf("♝%c", (j == 8) ? '\n' : ' ');
            else if (game->black_queens & pre_calculated_bit_shifts[index])
                printf("♛%c", (j == 8) ? '\n' : ' ');
            else if (game->black_king & pre_calculated_bit_shifts[index])
                printf("♚%c", (j == 8) ? '\n' : ' ');
            else if (game->white_pawns & pre_calculated_bit_shifts[index])
                printf("♙%c", (j == 8) ? '\n' : ' ');
            else if (game->white_rooks & pre_calculated_bit_shifts[index])
                printf("♖%c", (j == 8) ? '\n' : ' ');
            else if (game->white_knights & pre_calculated_bit_shifts[index])
                printf("♘%c", (j == 8) ? '\n' : ' ');
            else if (game->white_bishops & pre_calculated_bit_shifts[index])
                printf("♗%c", (j == 8) ? '\n' : ' ');
            else if (game->white_queens & pre_calculated_bit_shifts[index])
                printf("♕%c", (j == 8) ? '\n' : ' ');
            else if (game->white_king & pre_calculated_bit_shifts[index])
                printf("♔%c", (j == 8) ? '\n' : ' ');
            else
                printf(".%c", (j == 8) ? '\n' : ' ');
        }
    }
    printf("  a b c d e f g h\n");
}