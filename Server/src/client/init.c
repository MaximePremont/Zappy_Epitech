/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** init
*/

#include "server.h"

void init_client(client_t *client, int clifd, sockaddr_in_t addr_cli)
{
    client->fd = clifd;
    client->addr = addr_cli;
    client->disconnect = 0;
    client->player = NULL;
    strcpy(client->w_buffer, "");
    strcpy(client->r_buffer, "");
}

void assign_player_by_team(char *team_name, client_t *client,
job_t *job)
{
    char buffer[128];
    linked_player_t *player = job->head_player;
    char str[128] = "";

    while (player != NULL) {
        if (strcmp(player->player.team_name, team_name) == 0 &&
        player->player.state == UNUSED) {
            player->player.state = ALIVE;
            client->player = &player->player;
            sprintf(buffer, "%d\n%d %d\n",
            get_nb_unsued(job->head_player, team_name),
            job->map.width, job->map.height);
            append_to_string(client->player->w_buffer, buffer);
            sprintf(str, "%lu pns %d %d\n", clock(),
            client->player->id, ALIVE);
            append_to_gui(job, str);
            break;
        }
        player = player->next;
    }
}

void assign_player(char **args, client_t *client, job_t *job)
{
    if (is_valid_team(args[0], job)) {
        assign_player_by_team(args[0], client, job);
    } else {
        append_to_string(client->w_buffer, "ko\n");
    }
}
