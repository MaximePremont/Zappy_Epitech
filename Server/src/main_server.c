/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** main
*/

#include "server.h"
#include "args_manager.h"
#include "tools.h"

bool exit_server = false;

static void print_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height"
        "-n name1 name2 ... -c clientsNb -f freq"
        " the server socket listens.\n"
        "\tport\tis the port number\n"
        "\twidth\tis the width of the world\n"
        "\theight\tis the height of the world\n"
        "\tnameX\tis the name of the team X\n"
        "\tclientsNb\tis the number of authorized clients per team\n"
        "\tfreq\tis the reciprocal of time unit for execution of actions\n");
    exit(0);
}

void signal_handler(int sig)
{
    if (sig == SIGINT) {
        printf("\nServer is closing by signal...\n");
        exit_server = true;
    }
}

int main_server(int argc, char **argv)
{
    job_t job;
    network_t net = {.addr_serv = {0}};
    time_t t;

    srand((unsigned)time(&t));
    if (argc >= 2 && strcmp(argv[1], "-help") == 0)
        print_help();
    signal(SIGINT, signal_handler);
    init_job(argc, argv, &job);
    init_network(argc, argv, &net);
    start_server(&net);
    use_main_loop(&job, &net);
    destroy_everything(&job, &net);
    return 0;
}
