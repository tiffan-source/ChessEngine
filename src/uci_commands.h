
#ifndef UCI_COMMANDS_H
#define UCI_COMMANDS_H

#include "standard_lib.h"
#include "game.h"
#include "moves.h"
#include "move_generator.h"
#include "search_move.h"
#include "config.h"

#define COMMAND_MAX_LENGTH 256 * 4
#define UCI_RESPONSE_MAX_LENGTH 512

void handle_command(Game** game, const char* command, char* response);

#endif // UCI_COMMANDS_H
