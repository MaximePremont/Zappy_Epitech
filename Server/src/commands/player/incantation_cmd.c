/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** incantation_cmd
*/

#include "server.h"
#include "commands_tab.h"

const int player_tab[] = {1, 2, 2, 4, 4, 6, 6};
const int linemate_tab[] = {1, 1, 2, 1, 1, 1, 2};
const int deraumere_tab[] = {0, 1, 0, 1, 2, 2, 2};
const int sibur_tab[] = {0, 1, 1, 2, 1, 3, 2};
const int mendiane_tab[] = {0, 0, 0, 0, 3, 0, 2};
const int phiras_tab[] = {0, 0, 2, 1, 0, 1, 2};
const int thystame_tab[] = {0, 0, 0, 0, 0, 0, 1};

int nb_player_inxy(job_t *job, coords_t coords, int lvl)
{
    (void)GUI_COMMANDS;
    int i = 0;
    linked_player_t *tmp = job->head_player;

    while (tmp != NULL) {
        if (tmp->player.coords.x == coords.x &&
            tmp->player.coords.y == coords.y &&
            tmp->player.level == lvl)
            i++;
        tmp = tmp->next;
    }
    return i;
}

bool check_incantation(player_t *player, job_t *job)
{
    inventory_t inv = job->map.block[player->coords.y][player->coords.x];
    int linemate_nb = linemate_tab[player->level - 1];
    int deraumere_nb = deraumere_tab[player->level - 1];
    int sibur_nb = sibur_tab[player->level - 1];
    int mendiane_nb = mendiane_tab[player->level - 1];
    int phiras_nb = phiras_tab[player->level - 1];
    int thystame_nb = thystame_tab[player->level - 1];
    int player_nb = player_tab[player->level - 1];

    if (has_x_ressource(inv, LINEMATE, linemate_nb) &&
        has_x_ressource(inv, DERAUMERE, deraumere_nb) &&
        has_x_ressource(inv, SIBUR, sibur_nb) &&
        has_x_ressource(inv, MENDIANE, mendiane_nb) &&
        has_x_ressource(inv, PHIRAS, phiras_nb) &&
        has_x_ressource(inv, THYSTAME, thystame_nb) &&
        nb_player_inxy(job, player->coords, player->level)
        >= player_nb) {
        return true;
    } else
        return false;
}

void launch_all_incantations(player_t *player, job_t *job)
{
    char str_gui[48];
    linked_player_t *tmp = job->head_player;

    while (tmp != NULL) {
        if (tmp->player.coords.x == player->coords.x &&
            tmp->player.coords.y == player->coords.y &&
            tmp->player.level == player->level &&
            tmp->player.state == ALIVE &&
            tmp->player.id != player->id &&
            tmp->player.time_start == READY_FIRST_COMMAND) {
            append_to_string(tmp->player.w_buffer, "Elevation underway\n");
            enqueue_command_front(&tmp->player, NULL, &PLAYER_COMMANDS[13]);
            set_time(&tmp->player);
            sprintf(str_gui, " %d", tmp->player.id);
            append_to_gui(job, str_gui);
        }
        tmp = tmp->next;
    }
}

void start_incantation(player_t *player, char **args, job_t *job)
{
    (void)args;
    char str_gui[48];

    if (check_incantation(player, job)) {
        set_time(player);
        append_to_string(player->w_buffer, "Elevation underway\n");
        sprintf(str_gui, "%lu pic %d %d %d %d", player->time_start,
        player->coords.x, player->coords.y, player->level, player->id);
        append_to_gui(job, str_gui);
        launch_all_incantations(player, job);
        append_to_gui(job, "\n");
    } else {
        append_to_string(player->w_buffer, "ko\n");
        player->time_start = ERROR_FIRST_COMMAND;
    }
}
