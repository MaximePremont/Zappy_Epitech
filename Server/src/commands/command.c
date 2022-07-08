/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** command
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "command.h"
#include "commands_tab.h"
#include "tools.h"

void gui_command_connection(char **args, client_t *client)
{
    for (size_t i = 0; GUI_COMMANDS[i].cmd; i++) {
        if (strcmp(GUI_COMMANDS[i].cmd, args[0]) == 0) {
            enqueue_command(client->player, args, &GUI_COMMANDS[i]);
            break;
        }
    }
}

void player_command_connection(char **args, client_t *client)
{
    for (size_t i = 0; PLAYER_COMMANDS[i].cmd; i++) {
        if (strcmp(PLAYER_COMMANDS[i].cmd, args[0]) == 0) {
            enqueue_command(client->player, args, &PLAYER_COMMANDS[i]);
            break;
        }
    }
}

void use_command(char **args, client_t *client)
{
    if (strcmp(client->player->team_name, "GUI") == 0)
        gui_command_connection(args, client);
    else
        player_command_connection(args, client);
}
