/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** execute_buffer
*/

#include "server.h"

static bool is_empty(int readval, client_t *client)
{
    if (readval == 0) {
        client->disconnect = 1;
        return true;
    }
    return false;
}

void execute_buffer(int readval, char *read_buff, client_t *client, job_t *job)
{
    char buff[READ_BUFF_SIZE];
    int i = 0;

    if (is_empty(readval, client))
        return;
    read_buff[readval] = '\0';
    strcat(client->r_buffer, read_buff);
    while (client->r_buffer[i]) {
        buff[i] = client->r_buffer[i];
        if (buff[i] == '\n') {
            buff[i] = '\0';
            manage_readvalue(buff, client, job);
            strcpy(buff, "");
            memmove(client->r_buffer, client->r_buffer + i + 1,
            strlen(client->r_buffer) + i + 1);
            i = 0;
        } else
            i++;
    }
}
