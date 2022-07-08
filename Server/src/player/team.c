/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** team
*/

#include "player.h"

int get_nb_unsued(linked_player_t *head, char *team_name)
{
    int i = 0;
    linked_player_t *tmp = head;

    while (tmp != NULL) {
        if (strcmp(tmp->player.team_name, team_name) == 0 &&
            tmp->player.state == UNUSED)
            i++;
        tmp = tmp->next;
    }
    return i;
}

bool is_valid_team(char *name, job_t *job)
{
    for (int i = 0; i < job->nb_teams; i++) {
        if (strcmp(job->teams[i], name) == 0)
            return true;
    }
    return false;
}
