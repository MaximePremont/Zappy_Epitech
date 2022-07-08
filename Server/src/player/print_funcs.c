/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** print_funcs
*/

#include "server.h"

void print_player(player_t player)
{
    printf("[%s] PLAYER[%d] lvl[%d] state[%d]"
    " dir[%d] X[%d] Y[%d] t_a[%ld] t_f[%ld] to_w[%s]"
    " next_move[%s]\t",
    player.team_name,
    player.id,
    player.level,
    player.state,
    player.direction,
    player.coords.x,
    player.coords.y,
    player.time_start,
    player.time_to_eat,
    player.w_buffer,
    player.command[0]->cmd);
    print_inventory(player.inventory);
}

void print_players(linked_player_t *list)
{
    linked_player_t *tmp = list;

    while (tmp != NULL) {
        printf("name %d", tmp->player.id);
        print_player(tmp->player);
        tmp = tmp->next;
    }
}

void print_inventory(inventory_t inventory)
{
    printf("inv[food %d, linemate %d, deraumere %d, sibur %d, "
    "mendiane %d, phiras %d, thystame %d]\n",
    inventory.food,
    inventory.linemate,
    inventory.deraumere,
    inventory.sibur,
    inventory.mendiane,
    inventory.phiras,
    inventory.thystame);
}

void print_map(job_t *job)
{
    for (int i = 0; i != job->map.width; i++) {
        for (int j = 0; j != job->map.height; j++) {
            printf("Block[%d][%d] -> ", i, j);
            print_inventory(job->map.block[i][j]);
        }
    }
}
