/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** teams_cmd
*/

#include "server.h"

void teams_names(player_t *player, char **args, job_t *job)
{
    (void)args;
    (void)player;
    char str[128];
    int len = 0;

    for (; job->teams[len]; len++);
    sprintf(str, "0 tna %d", len);
    append_to_gui(job, str);
    for (int i = 0; job->teams[i]; i++) {
        sprintf(str, " %s", job->teams[i]);
        append_to_gui(job, str);
    }
    append_to_gui(job, "\n");
}

void pls(player_t *player, char **args, job_t *job)
{
    (void)player;
    (void)args;
    linked_player_t *tmp = job->head_player;
    char str[128];

    while (tmp != NULL) {
        if (strcmp(tmp->player.team_name, "GUI") != 0) {
            sprintf(str, "0 pnw %d %d %d %d %d %s\n", tmp->player.id,
            tmp->player.coords.x, tmp->player.coords.y,
            tmp->player.direction + 1,
            tmp->player.level, tmp->player.team_name);
            append_to_gui(job, str);
            simple_player_inv(&tmp->player, job);
            memset(str, 0, strlen(str));
        }
        tmp = tmp->next;
    }
}
