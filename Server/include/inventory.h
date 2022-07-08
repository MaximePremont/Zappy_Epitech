/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** inventory
*/

#ifndef INVENTORY_H_
    #define INVENTORY_H_

typedef struct inventory_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} inventory_t;

typedef enum ressource_s {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    ERROR
} ressource_t;

/**
** @brief Called to remove the ressources used for the incantation
** @param pl_lvl The level to know the amount of ressources to remove
** @param inv The inventory to which we remove the ressources
** @param job The structure containing all the game's informations
**/
void remove_incantation_res(int pl_lvl, inventory_t *inv, job_t *job);

/**
** @brief Called to send to the GUI the new state of the inventory
** of the player and the inventory of a certain tile
** @param player The player concerned
** @param inv The inventory othef the tile
** @param job The structure containing all the game's informations
**/
void send_new_invs(player_t player, inventory_t inv, job_t *job);

/**
** @brief Called to initialize an inventory
** @param inv The inventory concerned
**/
void init_inventory(inventory_t *inv);

/**
** @brief Called to print the content of an inventory
** @param inv The inventory concerned
**/
void print_inventory(inventory_t inventory);

/**
** @brief Called to remove n ressources from the given inventory
** @param inv The inventory concerned
** @param ressource The type of the ressource to be removed
** @param n The number of ressources you want to use
**/
void take_nressources(inventory_t *inv, ressource_t ressource, int n);

/**
** @brief Called to add n ressources to the given inventory
** @param inv The inventory concerned
** @param ressource The type of the ressource to be added
** @param n The number of ressources you want to use
**/
void give_nressources(inventory_t *inv, ressource_t ressource, int n);

/**
** @brief Called to check if the given inventory has x ressources
** @param inv The inventory concerned
** @param ressource The type of the ressource to be checked
** @param x The number of ressources you want to check
**/
bool has_x_ressource(inventory_t inv, ressource_t ressource, int x);

/**
** @brief Called to get the Type/id of the ressource given
** @param arg The string with the name of a ressource
**/
int get_ressource(char *arg);

/**
** @brief Called to get the number of ressource contained in
** the given inventory
** @param inv The inventory concerned
** @param ressource The id of the ressource to be checked
**/
int get_nb_ressource(inventory_t inv, ressource_t ressource);

#endif /* !INVENTORY_H_ */
