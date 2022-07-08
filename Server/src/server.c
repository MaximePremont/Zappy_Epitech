/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** server
*/

#include <sys/socket.h>
#include <unistd.h>

#include "client.h"
#include "server.h"
#include "errors_manager.h"

#include <stdio.h>

extern bool exit_server;

static void disconnect_player(player_t *player, job_t *job)
{
    char str[128];

    if (player) {
        player->state =
        (player->state != DEAD ? UNUSED : DEAD);
        sprintf(str, "%lu pns %d %d\n", clock(),
        player->id, UNUSED);
        append_to_gui(job, str);
        strcpy(str, "");
    }
}

static void disconnect_clients(linked_client_t **head, job_t *job)
{
    linked_client_t *tmp = *head;
    linked_client_t *to_destroy;

    while (tmp) {
        if (tmp->client.disconnect == 1 ||
        (tmp->client.player && tmp->client.player->state == DEAD)) {
            to_destroy = tmp;
            tmp = to_destroy->next;
            disconnect_player(to_destroy->client.player, job);
            close(to_destroy->client.fd);
            remove_client_node_by_fd(head, to_destroy->client.fd);
        }
        if (tmp != NULL)
            tmp = tmp->next;
    }
}

void use_main_loop(job_t *job, network_t *net)
{
    fd_set readset;
    fd_set writefds;

    while (!exit_server) {
        reset_set(&readset, net, net->head_client);
        reset_set(&writefds, net, net->head_client);
        select(FD_SETSIZE, &readset, &writefds, NULL, NULL);
        if (end_game(job) || exit_server)
            break;
        manage_client_connect(&readset, net);
        manage_client_msg(&readset, net, job);
        exec_command(job);
        write_buffer(net, &writefds);
        disconnect_clients(&net->head_client, job);
    }
}

void start_server(network_t *net)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;

    if (sockfd < 0)
        show_error("Can't create socket.");
    net->addr_serv = generate_addr(net->port);
    net->sock_size = sizeof(net->addr_serv);
    net->sockfd = sockfd;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        show_error("setsockopt error.");
    if (bind(sockfd, (sockaddr_t *)&net->addr_serv, net->sock_size) < 0)
        show_error("Can't bind socket.");
    if (listen(sockfd, MAX_CLIENTS) < 0)
        show_error("Can't listen sockets.");
}
