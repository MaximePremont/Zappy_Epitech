/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** socket
*/

#ifndef SOCKET_H
    #define SOCKET_H

    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>

/**
** @brief Called to intialize an address with the given port
** @param port The structure containing all the game's informations
**/
sockaddr_in_t generate_addr(const int port);

/**
** @brief Called to print the info of each tile of the map
** @param sockfd The structure containing all the game's informations
** @param clients The structure containing all the game's informations
**/
// void init_connects(int sockfd, client_t *clients);

/**
** @brief Called to reset the given set and then refill it with
** the existing clients
** @param set The fd_set to reset and refill
** @param net The structure containing the connection inforomations
** @param head The linked list of all the clients
**/
void reset_set(fd_set *set, network_t *net, linked_client_t *head);

#endif /* !SOCKET_H */
