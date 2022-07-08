/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** command
*/

#ifndef COMMAND_H
    #define COMMAND_H

typedef struct command_s command_t;
typedef struct coords_s coords_t;

    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include "server.h"
    #include "tools.h"
    #include "inventory.h"

void use_command(char **args, client_t *client);

typedef struct look_coords_s {
    int j;
    int k;
    int lx;
    int ly;
} look_coords_t;

typedef struct command_s {
    char *cmd;
    void (*use_function)(player_t *player, char **args, job_t *job);
    void (*end_function)(player_t *player, char **args, job_t *job);
    char **args;
    int time;
} command_t;

/**
** @brief Called when a player participating in an incantation
** reaches the end of the incantation
** @param player The player doing the action
** @param args The arguments given when launching the command
** @param job The structure containing all the game's informations
**/
void fake_end_incantation(player_t *player, char **args, job_t *job);

/**
** @brief Returns if the conditions of the incantation are met or not
** @param player The player doing the action
** @param job The structure containing all the game's informations
**/
bool check_incantation(player_t *player, job_t *job);

// Tests //
void use_cmd_users(player_t *player, char **args, job_t *job);
void end_cmd_users(player_t *player, char **args, job_t *job);
// ----------------------- //

// Command array //

/**
** @brief Called to add a command and it's arguments to the player's queue
** @param player The player in which we want to add the command
** @param args The arguments of the given command
** @param command The address of the command to be enqueued
**/
void enqueue_command(player_t *player, char **args, command_t *command);

/**
** @brief Called to add a command and it's arguments at the front of
** the player's queue
** @param player The player in which we want to add the command
** @param args The arguments of the given command
** @param command The address of the command to be enqueued
**/
void enqueue_command_front(player_t *player, char **args, command_t *command);

/**
** @brief Called to remove the first commmand of the player's queue
** @param player The player to which we want to remove the first command
**/
void dequeue_command(player_t *player);
// ----------------------- //

/**
** @brief Called to set the time to action of a player
** @param player The player to which we want to set the clock
**/
void set_time(player_t *player);

// COMMANDS //

/**
** @brief Called to start the take command
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_take(player_t *player, char **args, job_t *job);

/**
** @brief Called to end the take command, and actually do it
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void end_take(player_t *player, char **args, job_t *job);


/**
** @brief Called to start the drop command
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_drop(player_t *player, char **args, job_t *job);

/**
** @brief Called to end the drop command, and actually do it
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void end_drop(player_t *player, char **args, job_t *job);


/**
** @brief Called to start an incantation
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_incantation(player_t *player, char **args, job_t *job);

/**
** @brief Called to end the incantation
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void end_incantation(player_t *player, char **args, job_t *job);


/**
** @brief Called to start the fork command
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_fork(player_t *player, char **args, job_t *job);

/**
** @brief Called end the fork command, and actually do it
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void fork_player(player_t *player, char **args, job_t *job);

/**
** @brief Called to start the forward command
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_forward(player_t *player, char **args, job_t *job);

/**
** @brief Called to end the forward command, and actually do it
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void forward(player_t *player, char **args, job_t *job);

/**
** @brief Called to start the left command
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_left(player_t *player, char **args, job_t *job);

/**
** @brief Called to end the left command, and actually do it
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void left(player_t *player, char **args, job_t *job);

/**
** @brief Called to start the right command
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_right(player_t *player, char **args, job_t *job);

/**
** @brief Called to end the right command, and actually do it
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void right(player_t *player, char **args, job_t *job);

/**
** @brief Called to start the look command
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_look(player_t *player, char **args, job_t *job);

/**
** @brief Called to end the look command, and actually do it
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void look(player_t *player, char **args, job_t *job);

/**
** @brief Called to start the eject command
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_eject(player_t *player, char **args, job_t *job);

/**
** @brief Called to end eject command, and actually do it
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void eject_players(player_t *player, char **args, job_t *job);

/**
** @brief Called to start the broadcast command
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_broadcast(player_t *player, char **args, job_t *job);

/**
** @brief Called to end the broadcast command, and actually do it
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void broadcast(player_t *player, char **args, job_t *job);

/**
** @brief Called whenever a command does not need any verification
** before doing it
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void start_no_check(player_t *player, char **args, job_t *job);

/**
** @brief Called to kill a player and inform him
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void player_death(player_t *player, char **args, job_t *job);

/**
** @brief Called to get nb of unused players of the same team
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void nb_unused(player_t *player, char **args, job_t *job);

/**
** @brief Called to get the inventory of the player
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void inventory(player_t *player, char **args, job_t *job);

/**
** @brief Called to make the egg hatch an become a player
** @param player The player doing the command
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void hatch(player_t *player, char **args, job_t *job);
// ------------ //




// look utils //
/**
** @brief Called to add ressources to the look string
** @param player The player doing the action
** @param inv The inventory that is being checked
** @param total The total number of everything in this inventory
**/
void add_other_res(player_t *player, inventory_t inv, int total);

/**
** @brief Called to add ressources to the look string
** @param player The player doing the action
** @param inv The inventory that is being checked
** @param total The total number of everything in this inventory
**/
void add_res(player_t *player, inventory_t inv, int total);

/**
** @brief Called to add ressources to the look string
** @param player The player doing the action
** @param job The structure containing all the game's informations
** @param x the x coord of the inventory checked
** @param y the y coord of the inventory checked
**/
void append_each(player_t *player, job_t *job, int x, int y);


/**
** @brief Called to add a coma if needed wehn looking up
** @param player The player doing the action
** @param coords The structure containing the coords limits of the look
** @param i the coord of the case being looked
** @param n the coord of the case being looked
**/
void add_coma_u(player_t *player, look_coords_t coords, int i, int n);

/**
** @brief Called to add a coma if needed wehn looking right
** @param player The player doing the action
** @param coords The structure containing the coords limits of the look
** @param i the coord of the case being looked
** @param n the coord of the case being looked
**/
void add_coma_r(player_t *player, look_coords_t coords, int i, int n);

/**
** @brief Called to add a coma if needed wehn looking left
** @param player The player doing the action
** @param coords The structure containing the coords limits of the look
** @param i the coord of the case being looked
** @param n the coord of the case being looked
**/
void add_coma_l(player_t *player, look_coords_t coords, int i, int n);

/**
** @brief Called to add a coma if needed wehn looking down
** @param player The player doing the action
** @param coords The structure containing the coords limits of the look
** @param i the coord of the case being looked
** @param n the coord of the case being looked
**/
void add_coma_d(player_t *player, look_coords_t coords, int i, int n);

/**
** @brief Called to add ressources to the look string
** @param n the y coord of the inventory checked
** @param goal the y coord of the inventory checked
** @param lim the y coord of the inventory checked
**/
void fix_coord(int *n, int *goal, int lim);
//---------------//


// GUI COMMANDS //


/**
** @brief Called to get the information of the player's initialised
** @param player The player GUI
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void pls(player_t *player, char **args, job_t *job);

/**
** @brief Called to get the name's of the teams
** @param player The player GUI
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void teams_names(player_t *player, char **args, job_t *job);

/**
** @brief Called to get the size of the map
** @param player The player GUI
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void map_size(player_t *player, char **args, job_t *job);

/**
** @brief Called to get the content of a tile
** @param player The player GUI
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void tile_content(player_t *player, char **args, job_t *job);

/**
** @brief Called to get the content of the while map
** @param player The player GUI
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void map_content(player_t *player, char **args, job_t *job);

/**
** @brief Called to get the frequence
** @param player The player GUI
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void time_unit(player_t *player, char **args, job_t *job);

/**
** @brief Called to get the player_pos
** @param player The player GUI
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void player_pos(player_t *player, char **args, job_t *job);

/**
** @brief Called to get a player's level
** @param player The player GUI
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void player_lvl(player_t *player, char **args, job_t *job);

/**
** @brief Called to get a player's inventory
** @param player The player GUI
** @param args The arguments of the given command
** @param job The structure containing all the game's informations
**/
void player_inv(player_t *player, char **args, job_t *job);

// -------------- /


#endif /* !COMMAND_H */
