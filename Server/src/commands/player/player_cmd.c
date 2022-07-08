/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** player_cmd
*/

#include "server.h"
#include "commands_tab.h"

int get_nb_players(job_t *job, coords_t coords)
{
    int i = 0;
    linked_player_t *tmp = job->head_player;

    while (tmp != NULL) {
        if (tmp->player.coords.x == coords.x &&
            tmp->player.coords.y == coords.y)
            i++;
        tmp = tmp->next;
    }
    return i;
}

void nb_unused(player_t *player, char **args, job_t *job)
{
    (void)args;
    char value[6];

    sprintf(value, "%d\n", get_nb_unsued(job->head_player, player->team_name));
    append_to_string(player->w_buffer, value);
}

void start_fork(player_t *player, char **args, job_t *job)
{
    (void)args;
    (void)job;
    (void)GUI_COMMANDS;

    player->time_start = clock();
}

void fork_player(player_t *player, char **args, job_t *job)
{
    char str[48];
    (void)args;
    player_t egg;

    create_egg(&egg, player->team_name, job, player->coords);
    append_to_string(player->w_buffer, "ok\n");
    enqueue_command_front(&egg, NULL, &PLAYER_COMMANDS[12]);
    set_time(&egg);
    append_player_node(&job->head_player, egg);
    job->next_id++;
    sprintf(str, "%lu enw %d %d %d %d\n", egg.time_start, player->id, egg.id,
    player->coords.x, player->coords.y);
    append_to_gui(job, str);
    print_player(*player);
    print_player(egg);
}

void player_death(player_t *player, char **args, job_t *job)
{
    (void)args;
    char str[128];

    player->state = DEAD;
    set_time(player);
    append_to_string(player->w_buffer, "dead\n");
    sprintf(str, "%lu pdi %d\n", player->time_start, player->id);
    append_to_gui(job, str);
}
