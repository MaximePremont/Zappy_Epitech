/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** client_handle
*/

#include "command.h"
#include "errors_manager.h"
#include "socket.h"
#include "args_manager.h"

void manage_client_connect(fd_set *readset, network_t *net)
{
    int clifd = -1;
    sockaddr_in_t addr_cli;
    client_t new_client;

    if (FD_ISSET(net->sockfd, readset)) {
        clifd = accept(net->sockfd,
        (sockaddr_t *)&addr_cli, &net->sock_size);
        if (clifd < 0)
            show_error("Client connection error.");
        dprintf(clifd, "WELCOME\n");
        init_client(&new_client, clifd, addr_cli);
        append_client_node(&net->head_client, new_client);
    }
}

static void handle_first_message(char **args, client_t *client, job_t *job)
{
    if (strcmp(args[0], "GUI") == 0) {
        client->player = &job->head_player->player;
        client->player->state = ALIVE;
        append_to_string(client->player->w_buffer, "Welcome GUI\n");
    } else {
        assign_player(args, client, job);
    }
}

void manage_readvalue(char *buffer, client_t *client, job_t *job)
{
    size_t end = 0;
    char **args = NULL;

    for (; buffer[end] && buffer[end] != '\n' && buffer[end] != '\r'; end++);
    buffer[end] = '\0';
    if (strlen(buffer) > 0 && (buffer[0] == '\r' || buffer[0] == '\n'))
        return;
    if (verify_empty(buffer))
        return;
    create_args_list(&args, buffer);
    if (client->player == NULL)
        handle_first_message(args, client, job);
    else
        use_command(args, client);
    free_array(&args);
}

void manage_client_msg(fd_set *readset, network_t *net, job_t *job)
{
    char buffer[READ_BUFF_SIZE];
    ssize_t readval = 0;
    linked_client_t *tmp = net->head_client;

    while (tmp != NULL) {
        if (FD_ISSET(tmp->client.fd, readset)) {
            reset_buffer(buffer, READ_BUFF_SIZE);
            readval = read(tmp->client.fd, &buffer, READ_BUFF_SIZE - 1);
            execute_buffer(readval, buffer, &tmp->client, job);
        }
        tmp = tmp->next;
    }
}
