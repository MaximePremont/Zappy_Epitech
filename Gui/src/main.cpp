/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** main
*/

#include "args_manager.hpp"

int main(int const argc, char const **argv)
{
    zappy::args_manager args_manager(argc, argv);
    zappy::starter starter = args_manager.use();

    starter.start();
    return 0;
}
