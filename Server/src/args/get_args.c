/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** get_args
*/

#include <string.h>
#include <stdlib.h>
#include "errors_manager.h"

int get_port(int ac, char **av)
{
    int port = 8081;
    int i = 0;

    for (; i != ac; i++)
        if (strcmp(av[i], "-p") == 0)
            break;
    if (i == ac)
        return port;
    if (i + 1 >= ac || atoi(av[i + 1]) <= 0)
        show_error("Incorrect port given\n");
    port = atoi(av[i + 1]);
    return port;
}

int get_freq(int ac, char **av)
{
    int freq = 100;
    int i = 0;

    for (; i != ac; i++)
        if (strcmp(av[i], "-f") == 0)
            break;
    if (i == ac)
        return freq;
    if (i + 1 >= ac || atoi(av[i + 1]) <= 0)
        show_error("Incorrect frequence given\n");
    freq = atoi(av[i + 1]);
    return freq;
}

int get_width(int ac, char **av)
{
    int x = 10;
    int i = 0;

    for (; i != ac; i++)
        if (strcmp(av[i], "-x") == 0)
            break;
    if (i == ac)
        return x;
    if (i + 1 >= ac || atoi(av[i + 1]) <= 0)
        show_error("Incorrect width given\n");
    x = atoi(av[i + 1]);
    return x;
}

int get_height(int ac, char **av)
{
    int y = 10;
    int i = 0;

    for (; i != ac; i++)
        if (strcmp(av[i], "-y") == 0)
            break;
    if (i == ac)
        return y;
    if (i + 1 >= ac || atoi(av[i + 1]) <= 0)
        show_error("Incorrect height given\n");
    y = atoi(av[i + 1]);
    return y;
}

int get_nb_cli(int ac, char **av)
{
    int c = 3;
    int i = 0;

    for (; i != ac; i++)
        if (strcmp(av[i], "-c") == 0)
            break;
    if (i == ac)
        return c;
    if (i + 1 >= ac || atoi(av[i + 1]) <= 0)
        show_error("Incorrect clients number given\n");
    c = atoi(av[i + 1]);
    return c;
}
