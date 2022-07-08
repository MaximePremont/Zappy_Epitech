/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** starter
*/

#include <iostream>

#include "starter.hpp"

zappy::starter::starter(const std::string host, int port) :
    _host(host),
    _port(port)
{}

void zappy::starter::start() const
{
    std::string cmd = "cd ./Gui/Unity_out/ && ./zappy.x86_64";

    if (_port != -1)
        cmd += " " + std::to_string(_port) + " " + _host;
    if (std::system(cmd.c_str()) < 0) {
        std::cerr << "Can't start unity gui." << std::endl;
        std::exit(84);
    }
}
