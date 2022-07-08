/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** free
*/

#include "client.h"

void free_client(client_t *client)
{
    free(client);
}

void destroy_clients(linked_client_t *list)
{
    linked_client_t *tmp = list;

    while (tmp != NULL) {
        list = tmp->next;
        free_client(&tmp->client);
        tmp = list;
    }
}
