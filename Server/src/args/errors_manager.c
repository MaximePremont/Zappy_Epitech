/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** errors_manager
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void show_error(const char *error)
{
    printf("%s\n", error);
    exit(84);
}

void handle_errors(int argc, char **argv)
{
    if (argc < 2)
        show_error("Invalid number of arguments.");
    for (size_t i = 0; argv[1][i]; i++) {
        if (!isdigit(argv[1][i]))
            show_error("Port is not a number.");
    }
    if (atoi(argv[1]) < 0)
        show_error("Invalid port.");
}
