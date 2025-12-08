
#include "rooks_moves.h"

const int number_of_bit_in_rook_mask_for_square[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

const Bitboard rook_magic_numbers[64] = {
    0x8080044004918020,
    0xc4c0100020004008,
    0x0100104149002000,
    0x0080248010008800,
    0x4080040008000280,
    0x0100010012082400,
    0x2400081084221001,
    0x0200048040210402,
    0x0000800121804008,
    0x0424804000200080,
    0x00060010c20080a0,
    0x0004801000880180,
    0x0022002200101804,
    0x0022002200101804,
    0x0209000407000200,
    0x0001802040800300,
    0x0000808008401022,
    0x0100404000201000,
    0x0900490011002000,
    0x0884090030010021,
    0x0000808018002400,
    0x1011010004000208,
    0x0104040092104918,
    0x0200220000440081,
    0x0130800100210242,
    0x0001500040002000,
    0x0090021080200083,
    0x8002000e00102040,
    0x0002041100080100,
    0x4021002300081400,
    0x8000880400028110,
    0x2128106600008104,
    0x1040004aa0800080,
    0x1010420082002506,
    0x0004802006801000,
    0x1000981202002140,
    0x80c0380080800400,
    0x2040104408012040,
    0x0141000401002200,
    0x1000010842000884,
    0x1040804000258000,
    0xc00420100044c004,
    0x8805005020010044,
    0x6a00190010050020,
    0x800a000820060010,
    0x000400800a008004,
    0x1804108802040011,
    0x6000024084020001,
    0x2040008004406080,
    0x8a82002049009200,
    0x401004a000841080,
    0x0000838800900080,
    0x0084808800040180,
    0x0021800a01040080,
    0x00400d1e70480400,
    0x0000800041003880,
    0x0000800100304029,
    0x0020210082014212,
    0x0000102042002982,
    0x0800a0088d100101,
    0x0002001460081006,
    0x4046002801041002,
    0x4125000084120005,
    0x06000302468405a2
};

Bitboard pre_calculated_rook_moves_database[64][4096];

const Bitboard pre_calculated_rook_masks[64] = {
    0x000101010101017e,
    0x000202020202027c,
    0x000404040404047a,
    0x0008080808080876,
    0x001010101010106e,
    0x002020202020205e,
    0x004040404040403e,
    0x008080808080807e,
    0x0001010101017e00,
    0x0002020202027c00,
    0x0004040404047a00,
    0x0008080808087600,
    0x0010101010106e00,
    0x0020202020205e00,
    0x0040404040403e00,
    0x0080808080807e00,
    0x00010101017e0100,
    0x00020202027c0200,
    0x00040404047a0400,
    0x0008080808760800,
    0x00101010106e1000,
    0x00202020205e2000,
    0x00404040403e4000,
    0x00808080807e8000,
    0x000101017e010100,
    0x000202027c020200,
    0x000404047a040400,
    0x0008080876080800,
    0x001010106e101000,
    0x002020205e202000,
    0x004040403e404000,
    0x008080807e808000,
    0x0001017e01010100,
    0x0002027c02020200,
    0x0004047a04040400,
    0x0008087608080800,
    0x0010106e10101000,
    0x0020205e20202000,
    0x0040403e40404000,
    0x0080807e80808000,
    0x00017e0101010100,
    0x00027c0202020200,
    0x00047a0404040400,
    0x0008760808080800,
    0x00106e1010101000,
    0x00205e2020202000,
    0x00403e4040404000,
    0x00807e8080808000,
    0x007e010101010100,
    0x007c020202020200,
    0x007a040404040400,
    0x0076080808080800,
    0x006e101010101000,
    0x005e202020202000,
    0x003e404040404000,
    0x007e808080808000,
    0x7e01010101010100,
    0x7c02020202020200,
    0x7a04040404040400,
    0x7608080808080800,
    0x6e10101010101000,
    0x5e20202020202000,
    0x3e40404040404000,
    0x7e80808080808000
};


Bitboard generate_rook_moves_from_square_without_blocking_piece(Square square)
{
    Bitboard moves = 0x0ULL;

    int index_of_rank = square / 8;
    int index_of_file = square % 8;
    int i;

    // Generate moves along the rank (left and right)
    for (i = 0; i < 8; i++)
    {
        if (i != index_of_file)
        {
            Square target_square = (Square)(index_of_rank * 8 + i);
            moves = SET_BIT_ON_BITBOARD(moves, target_square);
        }
    }

    // Generate moves along the file (up and down)
    for (i = 0; i < 8; i++)
    {
        if (i != index_of_rank)
        {
            Square target_square = (Square)(i * 8 + index_of_file);
            moves = SET_BIT_ON_BITBOARD(moves, target_square);
        }
    }
    
    return moves;
}

Bitboard generate_rook_moves_from_square_without_blocking_piece_edge_remove(Square square)
{
    Bitboard moves = 0x0ULL;

    int index_of_rank = square / 8;
    int index_of_file = square % 8;
    int i;

    // Generate moves along the rank (left and right)
    for (i = 1; i < 7; i++)
    {
        if (i != index_of_file)
        {
            Square target_square = (Square)(index_of_rank * 8 + i);
            moves = SET_BIT_ON_BITBOARD(moves, target_square);
        }
    }

    // Generate moves along the file (up and down)
    for (i = 1; i < 7; i++)
    {
        if (i != index_of_rank)
        {
            Square target_square = (Square)(i * 8 + index_of_file);
            moves = SET_BIT_ON_BITBOARD(moves, target_square);
        }
    }
    
    return moves;
}

Bitboard get_rook_blocker_configuration_for_square_giving_index(Square square, int index)
{
    int index_bit;
    int i = 0;
    Bitboard blockers = generate_rook_moves_from_square_without_blocking_piece_edge_remove(square);
    
    Bitboard result = 0x0ULL;

    while ((index_bit = GET_LSB_INDEX(blockers)) != -1)
    {
        if (index & (1 << i))
        {
            result = SET_BIT_ON_BITBOARD(result, (Square)index_bit);
        }
        
        i++;
        blockers = CLEAR_BIT_ON_BITBOARD(blockers, (Square)index_bit);
    }
    
    return result;
}

int test_candidate_magic_bitboard_rook(Square square, Bitboard magic_number)
{
    int config_number = 1 << number_of_bit_in_rook_mask_for_square[square];
    int* index_table = calloc(config_number, sizeof(int));
    int i, index_found;

    for (i = 0; i < config_number; i++)
    {
        Bitboard blockers = get_rook_blocker_configuration_for_square_giving_index(square, i);

        index_found = HASH_FUNCTION_FOR_INDEXING_U64_CONFIGURATION(blockers, magic_number, number_of_bit_in_rook_mask_for_square[square]);

        if (index_table[index_found] != 0)
        {
            free(index_table);
            return 0; // Collision found
        }
        else
        {
            index_table[index_found] = i + 1; // Store i+1 to differentiate from default 0
        }
    }
    
    free(index_table);
    return 1; // No collision found
}

Bitboard generate_magic_number_for_rook_on_square(Square square)
{
    srandom(time(NULL));

    Bitboard magic;
    int test = 0;

    do{
        magic = RANDOM_U64_FEWBITS();
        test = test_candidate_magic_bitboard_rook(square, magic);
    }while (test == 0);

    return magic;
}

Bitboard* generate_all_magic_numbers_for_rooks()
{
    Bitboard* magic_numbers = malloc(sizeof(Bitboard) * 64);
    int i;

    for (i = 0; i < 64; i++)
    {
        magic_numbers[i] = generate_magic_number_for_rook_on_square((Square)i);
    }

    return magic_numbers;
}

Bitboard generate_rook_moves_for_giving_blocker_configuration(Square square, Bitboard blocker)
{
    Bitboard moves = 0x0ULL;

    int index_of_rank = square / 8;
    int index_of_file = square % 8;
    int i;

    // Generate moves to the top
    for (i = index_of_rank + 1; i < 8; i++)
    {
        Square target_square = (Square)(i * 8 + index_of_file);
        moves = SET_BIT_ON_BITBOARD(moves, target_square);
        if (blocker & pre_calculated_bit_shifts[target_square])
            break;
    }

    // Generate moves to the bottom
    for (i = index_of_rank - 1; i >= 0; i--)
    {
        Square target_square = (Square)(i * 8 + index_of_file);
        moves = SET_BIT_ON_BITBOARD(moves, target_square);
        if (blocker & pre_calculated_bit_shifts[target_square])
            break;
    }
    // Generate moves to the right
    for (i = index_of_file + 1; i < 8; i++)
    {
        Square target_square = (Square)(index_of_rank * 8 + i);
        moves = SET_BIT_ON_BITBOARD(moves, target_square);
        if (blocker & pre_calculated_bit_shifts[target_square])
            break;
    }
    // Generate moves to the left
    for (i = index_of_file - 1; i >= 0; i--)
    {
        Square target_square = (Square)(index_of_rank * 8 + i);
        moves = SET_BIT_ON_BITBOARD(moves, target_square);
        if (blocker & pre_calculated_bit_shifts[target_square])
            break;
    }

    return moves;
}


void initialize_pre_calculated_rook_moves_database()
{
    int square, config_number, i, index_by_magic;
    for (square = 0; square < 64; square++)
    {
        config_number = 1 << number_of_bit_in_rook_mask_for_square[square];
        for (i = 0; i < config_number; i++)
        {
            Bitboard blocker_configuration = get_rook_blocker_configuration_for_square_giving_index((Square)square, i);
            Bitboard moves = generate_rook_moves_for_giving_blocker_configuration((Square)square, blocker_configuration);
            index_by_magic = HASH_FUNCTION_FOR_INDEXING_U64_CONFIGURATION(blocker_configuration, rook_magic_numbers[square], number_of_bit_in_rook_mask_for_square[square]);
            pre_calculated_rook_moves_database[square][index_by_magic] = moves;
        }
    }
}

Bitboard retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(Square square, Bitboard blocker)
{
    Bitboard know_blocker_configuration = blocker & pre_calculated_rook_masks[square];
    int index_by_magic = HASH_FUNCTION_FOR_INDEXING_U64_CONFIGURATION(know_blocker_configuration
        , rook_magic_numbers[square], number_of_bit_in_rook_mask_for_square[square]);
    return pre_calculated_rook_moves_database[square][index_by_magic];
}

void generate_all_rooks_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard white_rooks = board_state->white_rooks;
    Bitboard black_rooks = board_state->black_rooks;
    Bitboard move, attack;

    if (board_state->turn == WHITE)
    {
        while(white_rooks){
            source_square = GET_LSB_INDEX(white_rooks);

            move = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(board_state)
            );


            while(move){
                target_square = GET_LSB_INDEX(move);

                if(pre_calculated_bit_shifts[target_square] & (WHITE_OCCUPENCY(board_state))){
                    move = CLEAR_BIT_ON_BITBOARD(move, target_square);
                    continue;
                } else {
                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        WHITE_ROOK,
                        pre_calculated_bit_shifts[target_square] & (BLACK_OCCUPENCY(board_state)) ? CAPTURE : QUIET_MOVES
                    );
                    move = CLEAR_BIT_ON_BITBOARD(move, target_square);
                }
            }

            white_rooks = CLEAR_BIT_ON_BITBOARD(white_rooks, source_square);
        }
    } else {
        while(black_rooks){
            source_square = GET_LSB_INDEX(black_rooks);

            move = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(board_state)
            );

            while(move){
                target_square = GET_LSB_INDEX(move);

                if(pre_calculated_bit_shifts[target_square] & (BLACK_OCCUPENCY(board_state))){
                    move = CLEAR_BIT_ON_BITBOARD(move, target_square);
                    continue;
                } else {
                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_ROOK,
                        pre_calculated_bit_shifts[target_square] & (WHITE_OCCUPENCY(board_state)) ? CAPTURE : QUIET_MOVES
                    );
                    move = CLEAR_BIT_ON_BITBOARD(move, target_square);
                }
            }
            black_rooks = CLEAR_BIT_ON_BITBOARD(black_rooks, source_square);
        }
    }
}

void generate_all_rooks_captures_from_game_state(Game* game, MoveList* move_list)
{
    Square source_square, target_square;
    Bitboard white_rooks = game->white_rooks;
    Bitboard black_rooks = game->black_rooks;
    Bitboard move, attack;

    if (game->turn == WHITE)
    {
        while(white_rooks){
            source_square = GET_LSB_INDEX(white_rooks);

            move = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(game)
            ) & BLACK_OCCUPENCY(game);


            while(move){
                target_square = GET_LSB_INDEX(move);

                move_list->moves[move_list->current_index++] = CREATE_MOVE(
                    source_square,
                    target_square,
                    WHITE_ROOK,
                    CAPTURE
                );
                move = CLEAR_BIT_ON_BITBOARD(move, target_square);
            }

            white_rooks = CLEAR_BIT_ON_BITBOARD(white_rooks, source_square);
        }
    } else {
        while(black_rooks){
            source_square = GET_LSB_INDEX(black_rooks);

            move = retrieve_pre_calculated_rook_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(game)
            ) & WHITE_OCCUPENCY(game);

            while(move){
                target_square = GET_LSB_INDEX(move);

                move_list->moves[move_list->current_index++] = CREATE_MOVE(
                    source_square,
                    target_square,
                    BLACK_ROOK,
                    CAPTURE
                );
                move = CLEAR_BIT_ON_BITBOARD(move, target_square);
            
            }
            black_rooks = CLEAR_BIT_ON_BITBOARD(black_rooks, source_square);
        }
    }
}