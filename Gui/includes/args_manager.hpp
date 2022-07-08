/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** args_manager
*/

#ifndef ARGS_MANAGER_HPP
    #define ARGS_MANAGER_HPP

    #include "starter.hpp"

namespace zappy {
    class args_manager {
        public:
            args_manager(const int argc, const char **argv);
            starter use();
        private:
            void show_error(std::string const message) const;

            void use_help() const;
            void use_port(std::string const arg);
            void use_host(std::string const arg);

            const int _argc;
            const char **_argv;
            int _port;
            std::string _host;
    };
}

#endif /* !ARGS_MANAGER_HPP */
