/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** starter
*/

#ifndef STARTER_HPP
    #define STARTER_HPP

    #include <string>

namespace zappy {
    class starter {
        public:
            starter(const std::string host = "ahldibk", const int port = -1);
            void start() const;
        private:
            const std::string _host;
            const int _port;
    };
}

#endif /* !ARGS_MANAGER_HPP */
