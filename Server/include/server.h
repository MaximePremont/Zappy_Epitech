/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** server
*/

#ifndef SERVER_H
    #define SERVER_H

typedef struct server_infos_s server_infos_t;
typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr sockaddr_t;

    #include <netinet/in.h>
    #include <sys/select.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdbool.h>

    #include "client.h"
    #include "player.h"

    #define MAX_CLIENTS 99

    #define EAT_TICK 126
    #define GEN_TICK 20

    #define READY_FIRST_COMMAND -1
    #define ERROR_FIRST_COMMAND -2

    #include "map.h"

typedef struct job_s {
    int next_id;
    int freq;
    int nb_teams;
    char **teams;
    map_t map;
    inventory_t global_inv;
    linked_player_t *head_player;
    long int time_gen;
} job_t;

typedef struct network_s {
    int port;
    int sockfd;
    sockaddr_in_t addr_serv;
    socklen_t sock_size;
    client_t *server_client;
    linked_client_t *head_client;
} network_t;


/**
** @brief The main function of the program
** @param argc The number of args
** @param argv The array of arguments
**/
int main_server(int argc, char **argv);

/**
** @brief Called to add the given string to the GUI's buffer
** to be written
** @param str The string to be added
** @param job The structure containing all the game's informations
**/
void append_to_gui(job_t *job, char *str);

/**
** @brief Called to initialize the network structure informations
** @param net The structure containing all the network's informations
**/
void start_server(network_t *net);

/**
** @brief Called to start the main loop and thus recieving, handling
** and sending informations
** @param net The structure containing all the network's informations
** @param job The structure containing all the game's informations
**/
void use_main_loop(job_t *job, network_t *net);

/**
** @brief Called to destroy/free every memory allocated in the program
** @param infos The structure containing all the game's informations
** @param net The structure containing all the network's informations
**/
void destroy_everything(job_t *infos, network_t *net);

/**
** @brief Called to initialize the network structure with the given arguments
** @param ac The number of args
** @param av The array of arguments
** @param net The structure containing all the network's informations
**/
void init_network(int ac, char **av, network_t *net);

/**
** @brief Called to initialize the job structure with the given arguments
** @param ac The number of args
** @param av The array of arguments
** @param job The structure containing all the game's informations
**/
void init_job(int ac, char **av, job_t *job);

/**
** @brief Called to generate ressources if needed every 20 ticks
** @param job The structure containing all the game's informations
**/
void gen_res_tick(job_t *job);

/**
** @brief Called to process the buffer read
** @param readval The output of the read function
** @param read_buff The buffer read by the read function
** @param client The client who sent the command
** @param job The structure containing all the game's informations
**/
void execute_buffer(int readval, char *read_buff,
client_t *client, job_t *job);

/**
** @brief Called to either return on a bad command recieve
** or handle if it is the first message recieved by this client
** or store it in the client's player queue
** @param buffer The buffer read by the read function
** @param client The client who sent the command
** @param job The structure containing all the game's informations
**/
void manage_readvalue(char *buffer, client_t *client, job_t *job);

/**
** @brief Called to end the game and the program
** @param job The structure containing all the game's informations
**/
bool end_game(job_t *job);

#endif /* !SERVER_H */
