/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** fake_end
*/

#include "server.h"

static void new_tile_content(coords_t coords, job_t *job)
{
    char str[128];
    int x = coords.x;
    int y = coords.y;

    sprintf(str, "0 bct %d %d %d %d %d %d %d %d %d\n", coords.x, coords.y,
    job->map.block[y][x].food,
    job->map.block[y][x].linemate,
    job->map.block[y][x].deraumere,
    job->map.block[y][x].sibur,
    job->map.block[y][x].mendiane,
    job->map.block[y][x].phiras,
    job->map.block[y][x].thystame);
    append_to_gui(job, str);
}

static void incantation_success(player_t *player, job_t *job)
{
    char str[32];
    char str_gui[64] = "";
    linked_player_t *tmp = job->head_player;
    int lvl = player->level;

    while (tmp != NULL) {
        if (tmp->player.coords.x == player->coords.x &&
            tmp->player.coords.y == player->coords.y &&
            tmp->player.level == lvl &&
            tmp->player.state == ALIVE) {
                tmp->player.level++;
                sprintf(str_gui, "0 plv %d %d\n",
                tmp->player.id, tmp->player.level);
                sprintf(str, "Current level: %d\n", tmp->player.level);
                append_to_string(tmp->player.w_buffer, str);
                append_to_gui(job, str_gui);
        }
        memset(str_gui, 0, strlen(str_gui));
        tmp = tmp->next;
    }
}

static void incantation_fail(player_t *player, job_t *job)
{
    char str_gui[48];
    linked_player_t *tmp = job->head_player;
    int lvl = player->level;

    while (tmp != NULL) {
        if (tmp->player.coords.x == player->coords.x &&
            tmp->player.coords.y == player->coords.y &&
            tmp->player.level == lvl &&
            tmp->player.state == ALIVE) {
                sprintf(str_gui, "%lu pie %d %d %d\n", tmp->player.time_start,
                tmp->player.coords.x, tmp->player.coords.y, 0);
                append_to_string(tmp->player.w_buffer, "ko\n");
        }
        tmp = tmp->next;
    }
}

void end_incantation(player_t *player, char **args, job_t *job)
{
    (void)args;
    char str_gui[64];
    inventory_t *inv = &job->map.block[player->coords.y][player->coords.x];

    if (check_incantation(player, job)) {
        remove_incantation_res(player->level, inv, job);
        new_tile_content(player->coords, job);
        incantation_success(player, job);
        sprintf(str_gui, "%lu pie %d %d %d\n",
        player->time_start, player->coords.x, player->coords.y, 1);
    } else
        incantation_fail(player, job);
    append_to_gui(job, str_gui);
}

void fake_end_incantation(player_t *player, char **args, job_t *job)
{
    (void)args;
    (void)player;
    (void)job;
}
