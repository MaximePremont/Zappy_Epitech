/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** ressources
*/

#include "server.h"

const int linemate_tab2[] = {1, 1, 2, 1, 1, 1, 2};
const int deraumere_tab2[] = {0, 1, 0, 1, 2, 2, 2};
const int sibur_tab2[] = {0, 1, 1, 2, 1, 3, 2};
const int mendiane_tab2[] = {0, 0, 0, 0, 3, 0, 2};
const int phiras_tab2[] = {0, 0, 2, 1, 0, 1, 2};
const int thystame_tab2[] = {0, 0, 0, 0, 0, 0, 1};

bool has_x_ressource(inventory_t inv, ressource_t ressource, int x)
{
    if (ressource == FOOD && inv.food < x)
        return false;
    if (ressource == LINEMATE && inv.linemate < x)
        return false;
    if (ressource == DERAUMERE && inv.deraumere < x)
        return false;
    if (ressource == SIBUR && inv.sibur < x)
        return false;
    if (ressource == MENDIANE && inv.mendiane < x)
        return false;
    if (ressource == PHIRAS && inv.phiras < x)
        return false;
    if (ressource == THYSTAME && inv.thystame < x)
        return false;
    return true;
}

void take_nressources(inventory_t *inv, ressource_t ressource, int n)
{
    if (ressource == FOOD)
        inv->food -= n;
    if (ressource == LINEMATE)
        inv->linemate -= n;
    if (ressource == DERAUMERE)
        inv->deraumere -= n;
    if (ressource == SIBUR)
        inv->sibur -= n;
    if (ressource == MENDIANE)
        inv->mendiane -= n;
    if (ressource == PHIRAS)
        inv->phiras -= n;
    if (ressource == THYSTAME)
        inv->thystame -= n;
}

void give_nressources(inventory_t *inv, ressource_t ressource, int n)
{
    if (ressource == FOOD)
        inv->food += n;
    if (ressource == LINEMATE)
        inv->linemate += n;
    if (ressource == DERAUMERE)
        inv->deraumere += n;
    if (ressource == SIBUR)
        inv->sibur += n;
    if (ressource == MENDIANE)
        inv->mendiane += n;
    if (ressource == PHIRAS)
        inv->phiras += n;
    if (ressource == THYSTAME)
        inv->thystame += n;
}

void remove_incantation_res(int pl_lvl, inventory_t *inv, job_t *job)
{
    take_nressources(inv, LINEMATE, linemate_tab2[pl_lvl - 1]);
    take_nressources(inv, DERAUMERE, deraumere_tab2[pl_lvl - 1]);
    take_nressources(inv, SIBUR, sibur_tab2[pl_lvl - 1]);
    take_nressources(inv, MENDIANE, mendiane_tab2[pl_lvl - 1]);
    take_nressources(inv, PHIRAS, phiras_tab2[pl_lvl - 1]);
    take_nressources(inv, THYSTAME, thystame_tab2[pl_lvl - 1]);
    give_nressources(&job->global_inv, LINEMATE,
    linemate_tab2[pl_lvl - 1]);
    give_nressources(&job->global_inv, DERAUMERE,
    deraumere_tab2[pl_lvl - 1]);
    give_nressources(&job->global_inv, SIBUR, sibur_tab2[pl_lvl - 1]);
    give_nressources(&job->global_inv, MENDIANE,
    mendiane_tab2[pl_lvl - 1]);
    give_nressources(&job->global_inv, PHIRAS, phiras_tab2[pl_lvl - 1]);
    give_nressources(&job->global_inv, THYSTAME,
    thystame_tab2[pl_lvl - 1]);
}
