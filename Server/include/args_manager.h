/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** args_manager
*/

#ifndef ARGS_MANAGER_H
    #define ARGS_MANAGER_H

    #include "server.h"

void reset_buffer(char *buffer, int len);
int get_port(int ac, char **av);
int get_freq(int ac, char **av);
int get_width(int ac, char **av);
int get_height(int ac, char **av);
int get_nb_cli(int ac, char **av);

#endif /* !ARGS_MANAGER_H */
