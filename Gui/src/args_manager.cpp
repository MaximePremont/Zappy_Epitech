/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** args_manager
*/

#include <iostream>

#include "args_manager.hpp"

zappy::args_manager::args_manager(const int argc, const char **argv) :
    _argc(argc),
    _argv(argv),
    _port(-1),
    _host("localhost")
{}

void zappy::args_manager::show_error(std::string const message) const
{
    std::cerr << message << std::endl;
    std::exit(84);
}

void zappy::args_manager::use_help() const
{
    if (_argc > 1 && !std::string(_argv[1]).compare("-help")) {
        std::cout << "USAGE: ./zappy_gui -p port -h machine\n\tport\tis the "
        "port number\n\tmachine\tis the name of the machine; localhost by "
        "default" << std::endl;
        exit(0);
    }
}

void zappy::args_manager::use_port(std::string const arg)
{
    try {
        _port = std::atoi(arg.c_str());
    } catch(const std::exception& e) {
        show_error("Invalid port number.");
    }
    if (_port < 0)
        show_error("Invalid port number.");
}

void zappy::args_manager::use_host(std::string const arg)
{
    if (arg.length() < 1)
        show_error("Invalid host.");
    _host = arg;
}

zappy::starter zappy::args_manager::use()
{
    use_help();
    for (int i = 1; i < _argc; i++) {
        if (!std::string(_argv[i]).compare("-p")) {
            if (i + 1 < _argc) {
                use_port(std::string(_argv[i + 1]));
                i++;
            } else {
                show_error("Invalid -p arg.");
            }
        }
        if (!std::string(_argv[i]).compare("-h")) {
            if (i + 1 < _argc) {
                use_host(std::string(_argv[i + 1]));
                i++;
            } else {
                show_error("Invalid -p arg.");
            }
        }
    }
    return starter(_host, _port);
}
