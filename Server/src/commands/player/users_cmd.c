/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** users_cmd
*/

#include "command.h"

void use_cmd_users(player_t *player, char **args, job_t *job)
{
    (void)args;
    (void)job;
    printf("Hello player n°%d in team %s\n", player->id, player->team_name);
    append_to_string(player->w_buffer, "Hello player\n");
    append_to_string(player->w_buffer, args[1]);
    append_to_string(player->w_buffer, "\n");
    player->time_start = clock();
}

void end_cmd_users(player_t *player, char **args, job_t *job)
{
    (void)args;
    (void)job;
    printf("It's the end command id: %d\n", player->id);
    append_to_string(player->w_buffer, "End of command\n");
}
