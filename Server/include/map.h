/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "inventory.h"

typedef struct job_s job_t;

typedef struct map_s {
    inventory_t **block;
    int width;
    int height;
} map_t;

/**
** @brief Called to print the info of each tile of the map
** @param infos The structure containing all the game's informations
**/
void print_map(job_t *infos);


/**
** @brief Called to generate the neede amount of ressources on the map
** @param job The structure containing all the game's informations
**/
void gen_res(job_t *job);

/**
** @brief Called to update a tile inventory on the GUI
** @param x The coordinate of the tile
** @param y The coordinate of the tile
** @param inv The tile's inventory
** @param job The structure containing all the game's informations
**/
void update_tile_inv(int x, int y, inventory_t inv, job_t *job);
#endif /* !MAP_H_ */
