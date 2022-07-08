/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** append_coma_conditions
*/

#include "server.h"

void add_coma_u(player_t *player, look_coords_t coords,
int i, int n)
{
    if (i + 1 != coords.ly || n + 1 != coords.lx) {
        append_to_string(player->w_buffer, ",");
    }
}

void add_coma_d(player_t *player, look_coords_t coords,
int i, int n)
{
    if (i - 1 != coords.ly || n - 1 != coords.lx) {
        append_to_string(player->w_buffer, ",");
    }
}

void add_coma_l(player_t *player, look_coords_t coords,
int i, int n)
{
    if (i - 1 != coords.lx || n + 1 != coords.ly) {
        append_to_string(player->w_buffer, ",");
    }
}

void add_coma_r(player_t *player, look_coords_t coords,
int i, int n)
{
    if (i + 1 != coords.lx || n - 1 != coords.ly) {
        append_to_string(player->w_buffer, ",");
    }
}
