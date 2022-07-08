/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** free_funcs
*/

#include "server.h"

void free_array(char ***largs)
{
    char **args = *largs;

    for (size_t i = 0; args[i]; i++) {
        free(args[i]);
    }
    free(*largs);
}

static void free_map(job_t *infos)
{
    for (int i = 0; i != infos->map.width; i++)
        free(infos->map.block[i]);
    free(infos->map.block);
}

static void free_teams(job_t *infos)
{
    for (int i = 0; infos->teams[i]; i++)
        free(infos->teams[i]);
    free(infos->teams);
}

void destroy_everything(job_t *job, network_t *net)
{
    free_map(job);
    free_teams(job);
    destroy_players(job->head_player);
    destroy_clients(net->head_client);
}
