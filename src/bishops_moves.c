

#include "bishops_moves.h"

const int number_of_bit_in_bishop_mask_for_square[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

const Bitboard bishop_magic_numbers[64] = {
    0x1088030708060080,
    0x0010900600404400,
    0x8210010065040400,
    0x0808284110080000,
    0x000311400080a000,
    0x4009104210106200,
    0x0003009814c04004,
    0x080040a804422000,
    0x2010c02a42860203,
    0x000020060c010220,
    0x2806101900410020,
    0x0800c42400880400,
    0x0001411040044001,
    0x0800031002100001,
    0x20000412060a2010,
    0x0504004444300818,
    0x2060000821040096,
    0x2060000821040096,
    0x0040808404008008,
    0x202a040440110000,
    0x4010100a02100812,
    0x8040200201942000,
    0x0049000484300240,
    0x0a288c0600430810,
    0x1420084120892510,
    0x4010230010140109,
    0x2041c50010040880,
    0x1020048048008010,
    0x0402820084010402,
    0x0012008101c82002,
    0x0401010042082910,
    0x0080490222010940,
    0x20018c4000200800,
    0x2201040242111000,
    0x0002080604040060,
    0x0200200800010104,
    0x0008020400001010,
    0x4060080480004040,
    0x0010090140220206,
    0x0404040040402100,
    0x2209045034204208,
    0x0500940120700800,
    0x048201a028000400,
    0x0034022011080800,
    0x440010020090aa05,
    0x0810409003002090,
    0x14360c0414018080,
    0x40a4008400400300,
    0x004405180a500010,
    0x0080c90410028000,
    0x020a2200840c8400,
    0x1000200020a80000,
    0x004c0012260212c0,
    0x01400420044c4184,
    0x80080805280208e1,
    0x41083000a20840c0,
    0x2408420150080c08,
    0x0040420222820841,
    0x0200400252080420,
    0xa004008001048803,
    0x20008004108a0200,
    0x20008004108a0200,
    0x8324a0a004028882,
    0x04a0212408015040
};

const Bitboard pre_calculated_bishop_masks[64] = {
    0x0040201008040200,
    0x0000402010080400,
    0x0000004020100a00,
    0x0000000040221400,
    0x0000000002442800,
    0x0000000204085000,
    0x0000020408102000,
    0x0002040810204000,
    0x0020100804020000,
    0x0040201008040000,
    0x00004020100a0000,
    0x0000004022140000,
    0x0000000244280000,
    0x0000020408500000,
    0x0002040810200000,
    0x0004081020400000,
    0x0010080402000200,
    0x0020100804000400,
    0x004020100a000a00,
    0x0000402214001400,
    0x0000024428002800,
    0x0002040850005000,
    0x0004081020002000,
    0x0008102040004000,
    0x0008040200020400,
    0x0010080400040800,
    0x0020100a000a1000,
    0x0040221400142200,
    0x0002442800284400,
    0x0004085000500800,
    0x0008102000201000,
    0x0010204000402000,
    0x0004020002040800,
    0x0008040004081000,
    0x00100a000a102000,
    0x0022140014224000,
    0x0044280028440200,
    0x0008500050080400,
    0x0010200020100800,
    0x0020400040201000,
    0x0002000204081000,
    0x0004000408102000,
    0x000a000a10204000,
    0x0014001422400000,
    0x0028002844020000,
    0x0050005008040200,
    0x0020002010080400,
    0x0040004020100800,
    0x0000020408102000,
    0x0000040810204000,
    0x00000a1020400000,
    0x0000142240000000,
    0x0000284402000000,
    0x0000500804020000,
    0x0000201008040200,
    0x0000402010080400,
    0x0002040810204000,
    0x0004081020400000,
    0x000a102040000000,
    0x0014224000000000,
    0x0028440200000000,
    0x0050080402000000,
    0x0020100804020000,
    0x0040201008040200
};

Bitboard pre_calculated_bishop_moves_database[64][512];

Bitboard generate_bishop_moves_from_square_without_blocking_piece(Square square)
{
    int rank = square / 8, r;
    int file = square % 8, f;
    Bitboard moves = 0x0ULL;

    // Up-right diagonal
    for (r = rank + 1, f = file + 1; r < 8 && f < 8; r++, f++) {
        moves = SET_BIT_ON_BITBOARD(moves, r * 8 + f);
    }

    // Down-left diagonal
    for (r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--) {
        moves = SET_BIT_ON_BITBOARD(moves, r * 8 + f);
    }

    // Up-left diagonal
    for (r = rank + 1, f = file - 1; r < 8 && f >= 0; r++, f--) {
        moves = SET_BIT_ON_BITBOARD(moves, r * 8 + f);
    }

    // Down-right diagonal
    for (r = rank - 1, f = file + 1; r >= 0 && f < 8; r--, f++) {
        moves = SET_BIT_ON_BITBOARD(moves, r * 8 + f);
    }

    return moves;
}

Bitboard generate_bishop_moves_from_square_without_blocking_piece_edge_remove(Square square)
{
    return generate_bishop_moves_from_square_without_blocking_piece(square) & ~CHESS_BOARDER;
}

Bitboard get_bishop_blocker_configuration_for_square_giving_index(Square square, int index)
{
    int index_bit;
    int i = 0;
    Bitboard blockers = generate_bishop_moves_from_square_without_blocking_piece_edge_remove(square);
    
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


int test_candidate_magic_bitboard_bishop(Square square, Bitboard magic_number)
{
    int config_number = 1 << number_of_bit_in_bishop_mask_for_square[square];
    int* index_table = calloc(config_number, sizeof(int));
    int i, index_found;

    for (i = 0; i < config_number; i++)
    {
        Bitboard blockers = get_bishop_blocker_configuration_for_square_giving_index(square, i);

        index_found = HASH_FUNCTION_FOR_INDEXING_U64_CONFIGURATION(blockers, magic_number, number_of_bit_in_bishop_mask_for_square[square]);

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

Bitboard generate_magic_number_for_bishop_on_square(Square square)
{
    srandom(time(NULL));

    Bitboard magic;
    int test = 0;

    do{
        magic = RANDOM_U64_FEWBITS();
        test = test_candidate_magic_bitboard_bishop(square, magic);
    }while (test == 0);

    return magic;
}

Bitboard* generate_all_magic_numbers_for_bishops()
{
    Bitboard* magic_numbers = malloc(sizeof(Bitboard) * 64);
    int i;

    for (i = 0; i < 64; i++)
    {
        magic_numbers[i] = generate_magic_number_for_bishop_on_square((Square)i);
    }

    return magic_numbers;
}

Bitboard generate_bishop_moves_for_giving_blocker_configuration(Square square, Bitboard blocker)
{
    int rank = square / 8, r;
    int file = square % 8, f;
    Bitboard moves = 0x0ULL;

    // Up-right diagonal
    for (r = rank + 1, f = file + 1; r < 8 && f < 8; r++, f++) {
        moves = SET_BIT_ON_BITBOARD(moves, r * 8 + f);
        if (blocker & (1ULL << (r * 8 + f))) break;
    }

    // Down-left diagonal
    for (r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--) {
        moves = SET_BIT_ON_BITBOARD(moves, r * 8 + f);
        if (blocker & (1ULL << (r * 8 + f))) break;
    }

    // Up-left diagonal
    for (r = rank + 1, f = file - 1; r < 8 && f >= 0; r++, f--) {
        moves = SET_BIT_ON_BITBOARD(moves, r * 8 + f);
        if (blocker & (1ULL << (r * 8 + f))) break;
    }

    // Down-right diagonal
    for (r = rank - 1, f = file + 1; r >= 0 && f < 8; r--, f++) {
        moves = SET_BIT_ON_BITBOARD(moves, r * 8 + f);
        if (blocker & (1ULL << (r * 8 + f))) break;
    }

    return moves;
}

void initialize_pre_calculated_bishop_moves_database()
{
    int square, config_number, i, index_by_magic;
    for (square = 0; square < 64; square++)
    {
        config_number = 1 << number_of_bit_in_bishop_mask_for_square[square];
        for (i = 0; i < config_number; i++)
        {
            Bitboard blockers = get_bishop_blocker_configuration_for_square_giving_index((Square)square, i);
            index_by_magic = HASH_FUNCTION_FOR_INDEXING_U64_CONFIGURATION(blockers, bishop_magic_numbers[square], number_of_bit_in_bishop_mask_for_square[square]);
            pre_calculated_bishop_moves_database[square][index_by_magic] = generate_bishop_moves_for_giving_blocker_configuration((Square)square, blockers);
        }
    }
}

Bitboard retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(Square square, Bitboard blocker)
{
    Bitboard know_blocker_configuration = blocker & pre_calculated_bishop_masks[square];
    int index_by_magic = HASH_FUNCTION_FOR_INDEXING_U64_CONFIGURATION(know_blocker_configuration, bishop_magic_numbers[square], number_of_bit_in_bishop_mask_for_square[square]);
    blocker = pre_calculated_bishop_moves_database[square][index_by_magic];
    return blocker;
}

void generate_all_bishop_moves_from_game_state(Game* board_state, MoveList* moves_list)
{
    Square source_square, target_square;
    Bitboard white_bishops = board_state->white_bishops;
    Bitboard black_bishops = board_state->black_bishops;
    Bitboard move, attack;

    if (board_state->turn == WHITE)
    {
        while(white_bishops){
            source_square = GET_LSB_INDEX(white_bishops);

            move = retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(board_state)
            );


            while(move){
                target_square = GET_LSB_INDEX(move);

                if((1ULL << target_square) & (WHITE_OCCUPENCY(board_state))){
                    move = CLEAR_BIT_ON_BITBOARD(move, target_square);
                    continue;
                } else {
                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        WHITE_BISHOP,
                        (1ULL << target_square) & (BLACK_OCCUPENCY(board_state)) ? CAPTURE : QUIET_MOVES
                    );
                    move = CLEAR_BIT_ON_BITBOARD(move, target_square);
                }
            }

            white_bishops = CLEAR_BIT_ON_BITBOARD(white_bishops, source_square);
        }
    } else {
        while(black_bishops){
            source_square = GET_LSB_INDEX(black_bishops);

            move = retrieve_pre_calculated_bishop_moves_for_giving_blocker_configuration(
                source_square,
                ALL_OCCUPENCY(board_state)
            );

            while(move){
                target_square = GET_LSB_INDEX(move);

                if((1ULL << target_square) & (BLACK_OCCUPENCY(board_state))){
                    move = CLEAR_BIT_ON_BITBOARD(move, target_square);
                    continue;
                } else {
                    moves_list->moves[moves_list->current_index++] = CREATE_MOVE(
                        source_square,
                        target_square,
                        BLACK_BISHOP,
                        (1ULL << target_square) & (WHITE_OCCUPENCY(board_state)) ? CAPTURE : QUIET_MOVES
                    );
                    move = CLEAR_BIT_ON_BITBOARD(move, target_square);
                }
            }

            black_bishops = CLEAR_BIT_ON_BITBOARD(black_bishops, source_square);
        }
    }
}