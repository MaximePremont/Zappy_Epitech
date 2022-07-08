/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** start_check
*/

#include "server.h"

void set_time(player_t *player)
{
    player->time_start = clock();
}

void start_no_check(player_t *player, char **args, job_t *job)
{
    (void)args;
    (void)job;
    set_time(player);
}
