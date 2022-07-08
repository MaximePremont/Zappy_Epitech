/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** socket
*/

#include "client.h"
#include "socket.h"

sockaddr_in_t generate_addr(const int port)
{
    sockaddr_in_t addr;

    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = port == 0 ? 0 : htons(port);
    return addr;
}

void reset_set(fd_set *set, network_t *net, linked_client_t *head)
{
    linked_client_t *tmp = head;

    FD_ZERO(set);
    FD_SET(net->sockfd, set);
    while (tmp) {
        if (tmp->client.fd >= 0) {
            FD_SET(tmp->client.fd, set);
        }
        tmp = tmp->next;
    }
}
