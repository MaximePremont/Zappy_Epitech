/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** inventory_cmd
*/

#include "server.h"

const char *RESSOURCES[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    NULL
};

void inventory(player_t *player, char **args, job_t *job)
{
    char inv[128];

    (void)job;
    (void)args;
    sprintf(inv, "[ food %d, linemate %d, deraumere %d, sibur %d, "
    "mendiane %d, phiras %d, thystame %d ]\n", player->inventory.food,
    player->inventory.linemate,
    player->inventory.deraumere,
    player->inventory.sibur,
    player->inventory.mendiane,
    player->inventory.phiras,
    player->inventory.thystame);
    append_to_string(player->w_buffer, inv);
}

int get_ressource(char *arg)
{
    size_t i = 0;

    if (!arg)
        return ERROR;
    for (; RESSOURCES[i]; i++) {
        if (strcmp(RESSOURCES[i], arg) == 0)
            break;
    }
    return i;
}

int get_nb_ressource(inventory_t inv, ressource_t ressource)
{
    if (ressource == FOOD)
        return inv.food;
    if (ressource == LINEMATE)
        return inv.linemate;
    if (ressource == DERAUMERE)
        return inv.deraumere;
    if (ressource == SIBUR)
        return inv.sibur;
    if (ressource == MENDIANE)
        return inv.mendiane;
    if (ressource == PHIRAS)
        return inv.phiras;
    if (ressource == THYSTAME)
        return inv.thystame;
    return 0;
}
