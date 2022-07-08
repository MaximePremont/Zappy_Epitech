/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** client
*/

#ifndef CLIENT_H
    #define CLIENT_H

typedef struct client_s client_t;
typedef struct linked_client_s linked_client_t;
typedef struct network_s network_t;

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/select.h>
    #include <signal.h>
    #include <stdbool.h>

    #include "server.h"
    #include "player.h"

    #define READ_BUFF_SIZE 8056
    #define CLIENT_W_BUFF_SIZE 8

typedef struct client_s {
    int fd;
    sockaddr_in_t addr;
    int disconnect;
    player_t *player;
    char w_buffer[CLIENT_W_BUFF_SIZE];
    char r_buffer[READ_BUFF_SIZE];
} client_t;

typedef struct linked_client_s {
    client_t client;
    struct linked_client_s *next;
} linked_client_t;

// Init //

/**
** @brief Called to initialize a new client
** @param client The structure of the client to be initialized
** @param clifd The fd/socket of the client
** @param addrcli The address of the clients
**/
void init_client(client_t *client, int clifd, sockaddr_in_t addr_cli);

/**
** @brief Called to assign a player to a client
** @param args The arguments containing the name of the team to be assigned to
** @param client The structure of the client
** @param job The structure containing all the game's informations
**/
void assign_player(char **args, client_t *client, job_t *job);
// ----------------------- //

// Manage //

/**
** @brief Called to accept a new client's connection
** @param readset The fd_scontaining the fds of the clients
** @param net The structure containing all the network's informations
**/
void manage_client_connect(fd_set *readset, network_t *net);

/**
** @brief Called to process a client's message
** @param readset The fd_scontaining the fds of the clients
** @param net The structure containing all the network's informations
** @param job The structure containing all the game's informations
**/
void manage_client_msg(fd_set *readset, network_t *net, job_t *job);
// ----------------------- //

// Linked //

/**
** @brief Called to append a client to the linked list
** @param list The list of all the clients
** @param client The structure of the client
**/
void append_client_node(linked_client_t **list, client_t client);

/**
** @brief Called to remove a client from the linked list
** @param list The list of all the clients
** @param destroy_fd The fd of the client to be removed
**/
void remove_client_node_by_fd(linked_client_t **list, int destroy_fd);

/**
** @brief Called to skip a client from the linked list
** @param list The list of all the clients
** @param destroy_fd The fd of the client to be skiped
**/
void skip_client_node_by_fd(linked_client_t **list, int skip_fd);
// ----------------------- //

// Print //

/**
** @brief Called to print all the clients informations
** @param list The list of all the clients
**/
void print_linked(linked_client_t *list);
// ----------------------- //

// Write //

/**
** @brief Called to write all the filled buffers if it is possible
** @param net The structure containing all the network's informations
** @param write_fds The fd_set containing alle the fds
** available to be written on
**/
void write_buffer(network_t *net, fd_set *writefds);
// ----------------------- //

// Destroy //

/**
** @brief Called to destroy/free all the clients
** @param list The list of all the clients

**/
void destroy_clients(linked_client_t *list);

/**
** @brief Called to free a client
** @param client The  client
**/
void free_client(client_t *client);
// ----------------------- //

#endif /* !CLIENT_H */
