/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** linked_player
*/

#include "player.h"
#include "errors_manager.h"

void append_player_node(linked_player_t **list, player_t player)
{
    linked_player_t *new_node =
    (linked_player_t *)malloc(sizeof(linked_player_t));
    linked_player_t *last = *list;

    if (new_node == NULL)
        show_error("Malloc fail.");
    new_node->player = player;
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

static void assign_node(linked_player_t **list, linked_player_t *tmp,
linked_player_t *prev)
{
    if (prev == NULL)
        *list = tmp->next;
    else
        prev->next = tmp->next;
}

void remove_player_node_by_id(linked_player_t **list, int destroy_id)
{
    linked_player_t *tmp = *list;
    linked_player_t *prev = NULL;

    while (tmp != NULL) {
        if (tmp->player.id == destroy_id) {
            assign_node(list, tmp, prev);
            free_player(&tmp->player);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void print_linked_player(linked_player_t *list)
{
    linked_player_t *tmp = list;

    while (tmp != NULL) {
        printf("-> player_fd: %d\n", tmp->player.id);
        tmp = tmp->next;
    }
    printf("----------\n");
}
