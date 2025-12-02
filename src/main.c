#include "move_generator.h"
#include "engine_settings.h"
#include "uci_commands.h"

int main(int argc, char *argv[]) {
    initialize_move_generation_databases();

    Game* internal_game = NULL;
    char command[COMMAND_MAX_LENGTH] = {0};
    char response[UCI_RESPONSE_MAX_LENGTH] = {0};

    setbuf(stdout, NULL);
    setbuf(stdin, NULL);


    while(fgets(command, COMMAND_MAX_LENGTH, stdin)) {
        fflush(stdout);

        handle_command(&internal_game, command, response);

        if (response[0] != '\0') {
            printf("%s", response);
        }

        if (strncmp(response, "QUIT", 4) == 0)
        {
            break;
        }
        

        memset(command, 0, COMMAND_MAX_LENGTH);
        memset(response, 0, UCI_RESPONSE_MAX_LENGTH);
    }

    if (internal_game)
    {
        free_game(internal_game);
    }
}