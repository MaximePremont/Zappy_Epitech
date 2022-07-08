/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** commands_tab
*/

#ifndef COMMANDS_TAB_H
    #define COMMANDS_TAB_H

    #include "command.h"

static command_t PLAYER_COMMANDS[] = {
    {"Forward", start_forward, forward, NULL, 7},
    {"Right", start_right, right, NULL, 7},
    {"Left", start_left, left, NULL, 7},
    {"Look", start_look, look, NULL, 7},
    {"Inventory", start_no_check, inventory, NULL, 1},
    {"Broadcast", start_broadcast, broadcast, NULL, 7},
    {"Connect_nbr", start_no_check, nb_unused, NULL, 0},
    {"Fork", start_fork, fork_player, NULL, 42},
    {"Eject", start_eject, eject_players, NULL, 7},
    {"Take", start_take, end_take, NULL, 7},
    {"Set", start_drop, end_drop, NULL, 7},
    {"Incantation", start_incantation, end_incantation, NULL, 300},
    {"Hatch", NULL, hatch, NULL, 600},
    {"fake_end", NULL, fake_end_incantation, NULL, 300},
    {NULL, NULL, NULL, NULL, 0}
};

static command_t GUI_COMMANDS[] = {
    {"msz", map_size, NULL, NULL, 0},
    {"bct", tile_content, NULL, NULL, 0},
    {"mct", map_content, NULL, NULL, 0},
    {"tna", teams_names, NULL, NULL, 0},
    {"ppo", player_pos, NULL, NULL, 0},
    {"plv", player_lvl, NULL, NULL, 0},
    {"pin", player_inv, NULL, NULL, 0},
    {"sgt", time_unit, NULL, NULL, 0},
    {"pls", pls, NULL, NULL, 0},
    {NULL, NULL, NULL, NULL, 0}
};

#endif /* !COMMANDS_TAB_H */
