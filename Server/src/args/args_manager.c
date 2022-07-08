/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** args_manager
*/

#include "server.h"
#include "args_manager.h"
#include "player.h"
#include "errors_manager.h"

void init_job(int ac, char **av, job_t *job)
{
    int nb_cli = get_nb_cli(ac, av);

    job->freq = get_freq(ac, av);
    job->map.width = get_width(ac, av);
    job->map.height = get_height(ac, av);
    job->next_id = 0;
    job->head_player = NULL;
    init_map(job);
    init_teams(ac, av, job);
    init_players(nb_cli, job);
    init_inventory(&job->global_inv);
    job->global_inv.food = 0;
    gen_res(job);
}

void init_network(int ac, char **av, network_t *net)
{
    net->port = get_port(ac, av);
    net->head_client = NULL;
    net->sock_size = sizeof(struct sockaddr_in);
    net->server_client = NULL;
    net->head_client = NULL;
    printf("Port: %d\n", net->port);
}

void reset_buffer(char *buffer, int len)
{
    for (int i = 0; i < len; i++)
        buffer[i] = '\0';
}
