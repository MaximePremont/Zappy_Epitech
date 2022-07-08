/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** initializers
*/

#include "server.h"
#include "errors_manager.h"

void init_inventory(inventory_t *inv)
{
    inv->food = 10;
    inv->deraumere = 0;
    inv->linemate = 0;
    inv->mendiane = 0;
    inv->phiras = 0;
    inv->sibur = 0;
    inv->thystame = 0;
}

void init_map(job_t *infos)
{
    infos->map.block = malloc(sizeof(inventory_t *) * (infos->map.width + 1));
    if (infos->map.block == NULL)
        show_error("Malloc fail.");
    for (int i = 0; i != infos->map.width; i++) {
        infos->map.block[i] = malloc(sizeof(inventory_t) *
        (infos->map.height + 1));
        if (infos->map.block[i] == NULL)
            show_error("Malloc fail.");
        for (int j = 0; j != infos->map.height; j++) {
            init_inventory(&infos->map.block[i][j]);
            infos->map.block[i][j].food = 0;
        }
    }
    infos->time_gen = clock();
}

void init_players(int nb_cli, job_t *job)
{
    player_t temp_player;

    create_player(&temp_player, "GUI", job);
    temp_player.coords.x = -1;
    temp_player.coords.y = -1;
    append_player_node(&job->head_player, temp_player);
    job->next_id++;
    for (int i = 0; job->teams[i]; i++) {
        for (int j = 0; j != nb_cli; j++, job->next_id++) {
            create_player(&temp_player, job->teams[i], job);
            append_player_node(&job->head_player, temp_player);
        }
    }
}
