/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** execution
*/

#include "server.h"

// -2 => error on the first command
// -1 => ready to execute first command

bool exec_first_func(player_t *player, job_t *job)
{
    if (player->time_start == READY_FIRST_COMMAND) {
        player->command[0]->use_function(
            player,
            player->command[0]->args,
            job);
        if (player->time_start == ERROR_FIRST_COMMAND ||
        player->command[0]->end_function == NULL) {
            player->time_start = READY_FIRST_COMMAND;
            dequeue_command(player);
            return false;
        }
    }
    return true;
}

void exec_end_func(player_t *player, job_t *job)
{
    double waiting = (clock() - player->time_start) / CLOCKS_PER_SEC;

    if (waiting >= (player->command[0]->time / job->freq)) {
        player->command[0]->end_function(
            player,
            player->command[0]->args,
            job);
        player->time_start = READY_FIRST_COMMAND;
        dequeue_command(player);
    }
}

void eat(player_t *player, job_t *job)
{
    double waiting = (clock() - player->time_to_eat) / CLOCKS_PER_SEC;

    if (waiting >= (EAT_TICK / job->freq)) {
        player->inventory.food--;
        if (player->inventory.food == 0) {
            player_death(player, NULL, job);
        } else
            player->time_to_eat = clock();
    }
}

void exec_command_player(player_t *player, job_t *job)
{
    if (player->state != DEAD && player->command[0] != NULL) {
        if (!exec_first_func(player, job))
            return;
        exec_end_func(player, job);
    }
}

void exec_command(job_t *job)
{
    linked_player_t *tmp = job->head_player;

    gen_res_tick(job);
    while (tmp) {
        if (tmp->player.command[0] != NULL)
            exec_command_player(&tmp->player, job);
        if (strcmp(tmp->player.team_name, "GUI") &&
        tmp->player.state == ALIVE)
            eat(&tmp->player, job);
        tmp = tmp->next;
    }
}
