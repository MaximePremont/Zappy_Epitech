/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** hatch_cmd
*/

#include "server.h"

void hatch(player_t *player, char **args, job_t *job)
{
    char str[16];
    (void)args;

    player->state = UNUSED;
    player->time_to_eat = clock();
    sprintf(str, "0 eht %d\n", player->id);
    append_to_gui(job, str);
}
