/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** errors_manager
*/

#ifndef ERRORS_MANAGER_H
    #define ERRORS_MANAGER_H

    #include <sys/socket.h>
    #include <unistd.h>

    #include "client.h"
    #include "socket.h"

/**
** @brief Called to check if there is an error
** @param argc nb of given args
** @param argv args given
**/
void handle_errors(int argc, char **argv);


/**
** @brief Called to display an error message and exit
** @param error The string of the error to be displayed
**/
void show_error(const char *error);

#endif /* !ERRORS_MANAGER_H */
