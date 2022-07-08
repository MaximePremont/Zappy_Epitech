/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** look_cmd
*/

#include "server.h"

void look_up(player_t *player, job_t *job)
{
    look_coords_t coords = {1, player->coords.x, player->coords.x + 1,
    player->coords.y + player->level + 1};

    append_to_string(player->w_buffer, "[");
    for (int i = player->coords.y; i != coords.ly;
    i++, coords.j += 2, coords.k -= 1) {
        fix_coord(&i, &coords.ly, job->map.height);
        fix_coord(&coords.k, NULL, job->map.width);
        coords.lx = coords.k + coords.j;
        for (int n = coords.k; n != coords.lx; n++) {
            fix_coord(&n, &coords.lx, job->map.width);
            append_each(player, job, n, i);
            add_coma_u(player, coords, i, n);
        }
    }
    append_to_string(player->w_buffer, " ]\n");
}

void look_down(player_t *player, job_t *job)
{
    look_coords_t coords = {1, player->coords.x, player->coords.x + 1,
    player->coords.y - player->level - 1};

    append_to_string(player->w_buffer, "[");
    for (int i = player->coords.y; i != coords.ly; i--,
    coords.j += 2, coords.k += 1) {
        fix_coord(&i, &coords.ly, job->map.height);
        fix_coord(&coords.k, NULL, job->map.width);
        coords.lx = coords.k - coords.j;
        for (int n = coords.k; n != coords.lx; n--) {
            fix_coord(&n, &coords.lx, job->map.width);
            append_each(player, job, n, i);
            add_coma_d(player, coords, i, n);
        }
    }
    append_to_string(player->w_buffer, " ]\n");
}

void look_right(player_t *player, job_t *job)
{
    look_coords_t coords = {1, player->coords.y,
    player->coords.x + player->level + 1, player->coords.y + 1};

    append_to_string(player->w_buffer, "[");
    for (int i = player->coords.x; i != coords.lx; i++,
    coords.j += 2, coords.k += 1) {
        fix_coord(&i, &coords.lx, job->map.width);
        fix_coord(&coords.k, NULL, job->map.height);
        coords.ly = coords.k - coords.j;
        for (int n = coords.k; n != coords.ly; n--) {
            fix_coord(&n, &coords.ly, job->map.height);
            append_each(player, job, i, n);
            add_coma_r(player, coords, i, n);
        }
    }
    append_to_string(player->w_buffer, " ]\n");
}

void look_left(player_t *player, job_t *job)
{
    look_coords_t coords = {1, player->coords.y,
    player->coords.x - player->level - 1, player->coords.y + 1};

    append_to_string(player->w_buffer, "[");
    for (int i = player->coords.x; i != coords.lx; i--,
    coords.j += 2, coords.k -= 1) {
        fix_coord(&i, &coords.lx, job->map.width);
        fix_coord(&coords.k, NULL, job->map.height);
        coords.ly = coords.k + coords.j;
        for (int n = coords.k; n != coords.ly; n++) {
            fix_coord(&n, &coords.ly, job->map.height);
            append_each(player, job, i, n);
            add_coma_l(player, coords, i, n);
        }
    }
    append_to_string(player->w_buffer, " ]\n");
}

void look(player_t *player, char **args, job_t *job)
{
    (void)args;

    if (player->direction == UP)
        look_up(player, job);
    if (player->direction == DOWN)
        look_down(player, job);
    if (player->direction == RIGHT)
        look_right(player, job);
    if (player->direction == LEFT)
        look_left(player, job);
}
