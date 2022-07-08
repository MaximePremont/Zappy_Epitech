/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** players_cmd
*/

#include "server.h"

void player_pos(player_t *player, char **args, job_t *job)
{
    (void)player;
    int n = atoi(args[1]);
    char str[16];
    linked_player_t *tmp = job->head_player;

    while (tmp != NULL) {
        if (tmp->player.id == n) {
            sprintf(str, "0 ppo %d %d %d %d\n", n, tmp->player.coords.x,
            tmp->player.coords.y,
            tmp->player.direction + 1);
            append_to_gui(job, str);
            break;
        }
        tmp = tmp->next;
    }
}

void player_lvl(player_t *player, char **args, job_t *job)
{
    (void)player;
    int n = atoi(args[1]);
    char str[16];
    linked_player_t *tmp = job->head_player;

    while (tmp != NULL) {
        if (tmp->player.id == n) {
            sprintf(str, "0 plv %d %d\n", n, tmp->player.level);
            append_to_gui(job, str);
            break;
        }
        tmp = tmp->next;
    }
}

void simple_player_inv(player_t *player, job_t *job)
{
    char str[128];

    sprintf(str, "0 pin %d %d %d %d %d %d %d %d\n", player->id,
    player->inventory.food, player->inventory.linemate,
    player->inventory.deraumere, player->inventory.sibur,
    player->inventory.mendiane,
    player->inventory.phiras,
    player->inventory.thystame);
    append_to_gui(job, str);
}

void player_inv(player_t *player, char **args, job_t *job)
{
    (void)player;
    int n = atoi(args[1]);
    char str[48];
    linked_player_t *tmp = job->head_player;

    while (tmp != NULL) {
        if (tmp->player.id == n) {
            sprintf(str, "0 pin %d %d %d %d %d %d %d %d\n", n,
            tmp->player.inventory.food, tmp->player.inventory.linemate,
            tmp->player.inventory.deraumere, tmp->player.inventory.sibur,
            tmp->player.inventory.mendiane,
            tmp->player.inventory.phiras,
            tmp->player.inventory.thystame);
            append_to_gui(job, str);
            break;
        }
        tmp = tmp->next;
    }
}

void send_new_invs(player_t player, inventory_t inv, job_t *job)
{
    char str[128];

    sprintf(str, "0 pin %d %d %d %d %d %d %d %d %d %d\n", player.id,
    player.coords.x, player.coords.y,
    player.inventory.food, player.inventory.linemate,
    player.inventory.deraumere, player.inventory.sibur,
    player.inventory.mendiane,
    player.inventory.phiras,
    player.inventory.thystame);
    sprintf(str, "%lu bct %d %d %d %d %d %d %d %d %d\n", clock(),
    player.coords.x, player.coords.y, inv.food, inv.linemate,
    inv.deraumere, inv.sibur, inv.mendiane, inv.phiras, inv.thystame);
    append_to_gui(job, str);
}
