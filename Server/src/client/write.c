/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** write
*/

#include "client.h"

void write_lines(int fd, char *buffer)
{
    char buff[WRITE_BUFF_SIZE];
    int i = 0;

    while (buffer[i]) {
        buff[i] = buffer[i];
        if (buff[i] == '\n') {
            buff[i + 1] = '\0';
            printf("SENDING [%s]\n", buff);
            dprintf(fd, "%s", buff);
            memmove(buffer, buffer + i + 1, strlen(buffer + i + 1) + 1);
            i = 0;
        } else
            i++;
    }
}

void write_client_buffer(client_t *client)
{
    if (strlen(client->w_buffer) != 0) {
        write_lines(client->fd, client->w_buffer);
        if (client->w_buffer[0] == '\0') {
            strcpy(client->w_buffer, "");
        }
    }
}

void write_player_buffer(client_t *client)
{
    if (client->player != NULL
    && strlen(client->player->w_buffer) != 0) {
        write_lines(client->fd, client->player->w_buffer);
        if (client->player->w_buffer[0] == '\0') {
            strcpy(client->player->w_buffer, "");
        }
    }
}

void write_buffer(network_t *net, fd_set *writefds)
{
    linked_client_t *tmp = net->head_client;

    while (tmp) {
        if (FD_ISSET(tmp->client.fd, writefds) && !tmp->client.disconnect) {
            write_client_buffer(&tmp->client);
            write_player_buffer(&tmp->client);
        }
        tmp = tmp->next;
    }
}

void append_to_gui(job_t *job, char *str)
{
    linked_player_t *tmp = job->head_player;

    while (tmp != NULL) {
        if (tmp->player.state == ALIVE &&
        strcmp(tmp->player.team_name, "GUI") == 0)
            append_to_string(tmp->player.w_buffer, str);
        tmp = tmp->next;
    }
}
