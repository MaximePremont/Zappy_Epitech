/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** command_array
*/

#include "command.h"
#include "errors_manager.h"

void init_command_0(player_t *player, char **args, command_t *command, int i)
{
    int j = 0;

    if (!player->command[0]) {
        player->command[0] = malloc(sizeof(*player->command[0]));
        player->command[0]->cmd = command->cmd;
        player->command[0]->use_function = command->use_function;
        player->command[0]->end_function = command->end_function;
        player->command[0]->time = command->time;
    }
    player->command[0]->args = malloc(sizeof(char *) * (count_args(args) + 1));
    if (player->command[i]->args == NULL)
        show_error("Malloc fail.");
    if (args) {
        for (j = 0; args[j]; j++)
            player->command[i]->args[j] = strdup(args[j]);
    }
    player->command[i]->args[j] = NULL;
}

void enqueue_command_front(player_t *player, char **args, command_t *command)
{
    int i = 0;

    for (i = 0; player->command[i]; i++);
    for (; i != 0; i--) {
        if (i == MAX_COMMAND - 1) {
            free(player->command[i]);
            player->command[i] = NULL;
        }
        player->command[i] = player->command[i - 1];
    }
    init_command_0(player, args, command, i);
}

void enqueue_command(player_t *player, char **args, command_t *command)
{
    int i = 0;
    int j = 0;
    int nb_args = count_args(args);

    for (i = 0; player->command[i]; i++);
    if (i >= MAX_COMMAND)
        return;
    if (!player->command[i]) {
        player->command[i] = malloc(sizeof(*player->command[i]));
        player->command[i]->cmd = command->cmd;
        player->command[i]->use_function = command->use_function;
        player->command[i]->end_function = command->end_function;
        player->command[i]->time = command->time;
    }
    player->command[i]->args = malloc(sizeof(char *) * (nb_args + 1));
    if (player->command[i]->args == NULL)
        show_error("Malloc fail.");
    for (j = 0; args[j]; j++)
        player->command[i]->args[j] = strdup(args[j]);
    player->command[i]->args[j] = NULL;
}

void dequeue_command(player_t *player)
{
    if (!player->command[0])
        return;
    if (player->command[0]->args)
        free_array(&(player->command[0]->args));
    free(player->command[0]);
    player->command[0] = NULL;
    for (int i = 0; player->command[i]; i++) {
        if (i == MAX_COMMAND - 1) {
            player->command[i] = NULL;
            break;
        }
        player->command[i] = player->command[i + 1];
    }
}
