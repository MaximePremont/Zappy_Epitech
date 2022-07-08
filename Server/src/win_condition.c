/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** win_condition
*/

#include "server.h"

static int is_lvl8(linked_player_t *tmp, job_t *job, int i)
{
    if (strcmp(tmp->player.team_name, job->teams[i]) == 0 &&
    tmp->player.level == 8)
        return 1;
    return 0;
}

bool end_game(job_t *job)
{
    int win = 0;
    char str[128] = "0 seg ";
    linked_player_t *tmp = job->head_player;

    for (int i = 0; job->teams[i]; i++) {
        while (tmp != NULL) {
            win += is_lvl8(tmp, job, i);
            tmp = tmp->next;
        }
        if (win >= 6) {
            strcat(strcat(str, job->teams[i]), "\n");
            append_to_gui(job, str);
            return true;
        }
        win = 0;
        tmp = job->head_player;
    }
    return false;
}
