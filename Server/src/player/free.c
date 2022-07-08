/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** free
*/

#include "player.h"

void free_player(player_t *player)
{
    for (int i = 0; player->command[i]; i++) {
        free_array(&player->command[i]->args);
        free(player->command[i]);
        player->command[i] = NULL;
    }
    free(player);
}

void destroy_players(linked_player_t *list)
{
    linked_player_t *tmp = list;
    linked_player_t *prev = NULL;

    while (tmp != NULL) {
        prev = tmp;
        tmp = tmp->next;
        free_player(&prev->player);
    }
}
