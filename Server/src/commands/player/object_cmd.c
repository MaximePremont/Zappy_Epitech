/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** object_cmd
*/

#include "server.h"

void start_take(player_t *player, char **args, job_t *job)
{
    char str[128];
    inventory_t *inv = &job->map.block[player->coords.y][player->coords.x];
    ressource_t ressource = get_ressource(args[1]);

    if (ressource == ERROR) {
        append_to_string(player->w_buffer, "ko\n");
        player->time_start = ERROR_FIRST_COMMAND;
        return;
    }
    if (!has_x_ressource(*inv, ressource, 1)) {
        append_to_string(player->w_buffer, "ko\n");
        player->time_start = ERROR_FIRST_COMMAND;
        return;
    }
    set_time(player);
    sprintf(str, "%lu pgt %d %d\n", player->time_start, player->id, ressource);
    append_to_gui(job, str);
}

void start_drop(player_t *player, char **args, job_t *job)
{
    char str[128];
    ressource_t ressource = get_ressource(args[1]);

    if (ressource == ERROR) {
        append_to_string(player->w_buffer, "ko\n");
        player->time_start = ERROR_FIRST_COMMAND;
        return;
    }
    if (!has_x_ressource(player->inventory, ressource, 1)) {
        append_to_string(player->w_buffer, "ko\n");
        player->time_start = ERROR_FIRST_COMMAND;
        return;
    }
    set_time(player);
    sprintf(str, "%lu pdr %d %d\n", player->time_start, player->id, ressource);
    append_to_gui(job, str);
}

bool can_take_end(ressource_t ressource, player_t *player,
job_t *job, inventory_t *inv)
{
    char str[128];

    if (ressource == ERROR) {
        append_to_string(player->w_buffer, "ko\n");
        sprintf(str, "%lu pgte %d %d\n", player->time_start, player->id, 0);
        append_to_gui(job, str);
        return false;
    } else if (!has_x_ressource(*inv, ressource, 1)) {
        append_to_string(player->w_buffer, "ko\n");
        sprintf(str, "%lu pgte %d %d\n", player->time_start, player->id, 0);
        append_to_gui(job, str);
        return false;
    }
    return true;
}

void end_take(player_t *player, char **args, job_t *job)
{
    char str[128];
    inventory_t *inv = &job->map.block[player->coords.y][player->coords.x];
    ressource_t ressource = get_ressource(args[1]);

    if (!can_take_end(ressource, player, job, inv))
        return;
    take_nressources(inv, ressource, 1);
    take_nressources(&job->global_inv, ressource, 1);
    give_nressources(&player->inventory, ressource, 1);
    append_to_string(player->w_buffer, "ok\n");
    sprintf(str, "%lu pgte %d %d\n", player->time_start, player->id, 1);
    append_to_gui(job, str);
    send_new_invs(*player, *inv, job);
}

void end_drop(player_t *player, char **args, job_t *job)
{
    inventory_t *inv = &job->map.block[player->coords.y][player->coords.x];
    ressource_t ressource = get_ressource(args[1]);

    if (ressource == ERROR) {
        append_to_string(player->w_buffer, "ko\n");
        return;
    }
    if (!has_x_ressource(player->inventory, ressource, 1)) {
        append_to_string(player->w_buffer, "ko\n");
        return;
    }
    take_nressources(&player->inventory, ressource, 1);
    give_nressources(inv, ressource, 1);
    give_nressources(&(job->global_inv), ressource, 1);
    print_inventory(job->global_inv);
    append_to_string(player->w_buffer, "ok\n");
    send_new_invs(*player, *inv, job);
}
