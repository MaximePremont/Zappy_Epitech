/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** client
*/

#include "client.h"
#include "errors_manager.h"

void append_client_node(linked_client_t **list, client_t client)
{
    linked_client_t *new_node =
    (linked_client_t *)malloc(sizeof(linked_client_t));
    linked_client_t *last = *list;

    if (new_node == NULL) {
        client.disconnect = 1;
        show_error("Malloc fail.");
        return;
    }
    new_node->client = client;
    new_node->next = NULL;
    if (*list == NULL) {
        *list = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}

static void assign_node(linked_client_t **list, linked_client_t *tmp,
linked_client_t *prev)
{
    if (prev == NULL)
        *list = tmp->next;
    else
        prev->next = tmp->next;
}

void remove_client_node_by_fd(linked_client_t **list, int destroy_fd)
{
    linked_client_t *tmp = *list;
    linked_client_t *prev = NULL;

    while (tmp != NULL) {
        if (tmp->client.fd == destroy_fd) {
            assign_node(list, tmp, prev);
            free_client(&tmp->client);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void skip_client_node_by_fd(linked_client_t **list, int destroy_fd)
{
    linked_client_t *tmp = *list;
    linked_client_t *prev = NULL;

    while (tmp != NULL) {
        if (tmp->client.fd == destroy_fd) {
            assign_node(list, tmp, prev);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void print_linked(linked_client_t *list)
{
    linked_client_t *tmp = list;

    while (tmp != NULL) {
        printf("-> client_fd: %d\n", tmp->client.fd);
        tmp = tmp->next;
    }
    printf("----------\n");
}
