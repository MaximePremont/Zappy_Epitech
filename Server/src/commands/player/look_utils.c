/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** look_utils
*/

#include "server.h"

void add_other_res(player_t *player, inventory_t inv, int total)
{
    int mendiane = get_nb_ressource(inv, MENDIANE);
    int phiras = get_nb_ressource(inv, PHIRAS);
    int thystame = get_nb_ressource(inv, THYSTAME);

    for (int i = 0; i != mendiane; i++, total++)
        append_to_string(player->w_buffer, " mendiane");
    for (int i = 0; i != phiras; i++, total++)
        append_to_string(player->w_buffer, " phiras");
    for (int i = 0; i != thystame; i++, total++)
        append_to_string(player->w_buffer, " thystame");
    if (total == 0)
        append_to_string(player->w_buffer, " ");
}

void add_res(player_t *player, inventory_t inv, int total)
{
    int linemate = get_nb_ressource(inv, LINEMATE);
    int deraumere = get_nb_ressource(inv, DERAUMERE);
    int sibur = get_nb_ressource(inv, SIBUR);

    for (int i = 0; i != linemate; i++, total++)
        append_to_string(player->w_buffer, " linemate");
    for (int i = 0; i != deraumere; i++, total++)
        append_to_string(player->w_buffer, " deraumere");
    for (int i = 0; i != sibur; i++, total++)
        append_to_string(player->w_buffer, " sibur");
    add_other_res(player, inv, total);
}

void append_each(player_t *player, job_t *job, int x, int y)
{
    coords_t xy = {x, y};
    inventory_t inv = job->map.block[xy.y][xy.x];
    int nb_players = get_nb_players(job, xy);
    int food = get_nb_ressource(inv, FOOD);
    int total = 0;

    for (int i = 0; i != nb_players; i++, total++)
        append_to_string(player->w_buffer, " player");
    for (int i = 0; i != food; i++, total++)
        append_to_string(player->w_buffer, " food");
    add_res(player, inv, total);
}

void fix_coord(int *n, int *goal, int lim)
{
    if (goal == NULL && *n == lim)
        *n = 0;
    else if (goal == NULL && *n < 0)
        *n = lim - 1;
    if (*n == lim) {
        *n = 0;
        *goal -= lim;
    } else if (*n < 0) {
        *n = lim - 1;
        *goal += lim;
    }
}
