/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** eject_cmd
*/

#include "server.h"

direction_t opposite_d(direction_t direction)
{
    if (direction == UP)
        return DOWN;
    if (direction == DOWN)
        return UP;
    if (direction == RIGHT)
        return LEFT;
    if (direction == LEFT)
        return RIGHT;
    return UP;
}

void eject_in_direction(player_t *player, direction_t direction, job_t *job)
{
    char str[3];

    move_direction(player, direction);
    check_limits(player, job);
    append_to_string(player->w_buffer, "eject: ");
    sprintf(str, "%d\n", opposite_d(direction));
    append_to_string(player->w_buffer, str);
}

void show_ejected(player_t player, job_t *job)
{
    char str[128];

    sprintf(str, "0 pexed %d %d %d\n", player.id,
    player.coords.x, player.coords.y);
    append_to_gui(job, str);
    memset(str, 0, strlen(str));
}

void eject_players(player_t *player, char **args, job_t *job)
{
    (void)args;
    linked_player_t *tmp = job->head_player;

    while (tmp != NULL) {
        if (tmp->player.id != player->id &&
            player->coords.x == tmp->player.coords.x &&
            player->coords.y == tmp->player.coords.y) {
            eject_in_direction(&tmp->player, player->direction, job);
            show_ejected(tmp->player, job);
        }
        tmp = tmp->next;
    }
    append_to_string(player->w_buffer, "ok\n");
}

void start_eject(player_t *player, char **args, job_t *job)
{
    (void)args;
    linked_player_t *tmp = job->head_player;
    player_t fake_player;
    char str[128];

    set_time(player);
    sprintf(str, "%lu pex %d\n", player->time_start, player->id);
    append_to_gui(job, str);
    while (tmp != NULL) {
        if (tmp->player.id != player->id &&
        player->coords.x == tmp->player.coords.x &&
        player->coords.y == tmp->player.coords.y) {
            fake_player = tmp->player;
            eject_in_direction(&fake_player, player->direction, job);
        }
        tmp = tmp->next;
    }
}
