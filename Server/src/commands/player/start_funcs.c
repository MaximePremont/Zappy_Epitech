/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** start_funcs
*/

#include "server.h"

void start_forward(player_t *player, char **args, job_t *job)
{
    (void)args;
    player_t temp = *player;
    char str[128];

    set_time(player);
    forward(&temp, args, job);
    sprintf(str, "%lu ppo %d %d %d %d\n", player->time_start, temp.id,
    temp.coords.x, temp.coords.y,
    temp.direction + 1);
    append_to_gui(job, str);
}

void start_right(player_t *player, char **args, job_t *job)
{
    (void)args;
    player_t temp = *player;
    char str[128];

    set_time(player);
    right(&temp, args, job);
    sprintf(str, "%lu ppo %d %d %d %d\n", player->time_start, temp.id,
    temp.coords.x, temp.coords.y,
    temp.direction + 1);
    append_to_gui(job, str);
}

void start_left(player_t *player, char **args, job_t *job)
{
    (void)args;
    player_t temp = *player;
    char str[128];

    set_time(player);
    left(&temp, args, job);
    sprintf(str, "%lu ppo %d %d %d %d\n", player->time_start, temp.id,
    temp.coords.x, temp.coords.y,
    temp.direction + 1);
    append_to_gui(job, str);
}

void start_look(player_t *player, char **args, job_t *job)
{
    (void)args;
    char str[128];

    set_time(player);
    sprintf(str, "%lu look %d\n", player->time_start, player->id);
    append_to_gui(job, str);
}

void start_broadcast(player_t *player, char **args, job_t *job)
{
    char str[1128];

    set_time(player);
    if (!args || !args[1])
        return;
    sprintf(str, "%lu pbc %d %s\n", player->time_start, player->id, args[1]);
    append_to_gui(job, str);
}
