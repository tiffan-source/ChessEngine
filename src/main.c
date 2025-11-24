#include "game.h"
#include <time.h>

int main()
{
    print_representation_of_chess_game(create_game_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));
    return 0;
}