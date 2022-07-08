/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** generate_ressources
*/

#include "server.h"

const float density_tab[] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};

static void add_other_res_rand(job_t *job, ressource_t ressource,
int x, int y)
{
    if (ressource == MENDIANE) {
        job->map.block[y][x].mendiane++;
        job->global_inv.mendiane++;
        update_tile_inv(x, y, job->map.block[y][x], job);
    }
    if (ressource == PHIRAS) {
        job->map.block[y][x].phiras++;
        job->global_inv.phiras++;
        update_tile_inv(x, y, job->map.block[y][x], job);
    }
    if (ressource == THYSTAME) {
        job->map.block[y][x].thystame++;
        job->global_inv.thystame++;
        update_tile_inv(x, y, job->map.block[y][x], job);
    }
    if (ressource == SIBUR) {
        job->map.block[y][x].sibur++;
        job->global_inv.sibur++;
        update_tile_inv(x, y, job->map.block[y][x], job);
    }
}

static void add_res_rand(job_t *job, ressource_t ressource)
{
    int x = rand() % job->map.width;
    int y = rand() % job->map.height;

    if (ressource == FOOD) {
        job->map.block[y][x].food++;
        job->global_inv.food++;
        update_tile_inv(x, y, job->map.block[y][x], job);
    }
    if (ressource == LINEMATE) {
        job->map.block[y][x].linemate++;
        job->global_inv.linemate++;
        update_tile_inv(x, y, job->map.block[y][x], job);
    }
    if (ressource == DERAUMERE) {
        job->map.block[y][x].deraumere++;
        job->global_inv.deraumere++;
        update_tile_inv(x, y, job->map.block[y][x], job);
    }
    add_other_res_rand(job, ressource, x, y);
}

static void gen_other_res(job_t *job)
{
    int nb_phiras = job->map.width * job->map.height * density_tab[PHIRAS]
    - job->global_inv.phiras;
    int nb_thystame = job->map.width * job->map.height * density_tab[THYSTAME]
    - job->global_inv.thystame;
    int nb_mendiane = job->map.width * job->map.height * density_tab[MENDIANE]
    - job->global_inv.mendiane;

    for (; nb_mendiane > 0; nb_mendiane--)
        add_res_rand(job, MENDIANE);
    for (; nb_phiras > 0; nb_phiras--)
        add_res_rand(job, PHIRAS);
    for (; nb_thystame > 0; nb_thystame--)
        add_res_rand(job, THYSTAME);
}

void gen_res(job_t *job)
{
    int nb_food = job->map.width * job->map.height * density_tab[FOOD]
    - job->global_inv.food;
    int nb_linemate = job->map.width * job->map.height * density_tab[LINEMATE]
    - job->global_inv.linemate;
    int nb_der = job->map.width * job->map.height * density_tab[DERAUMERE]
    - job->global_inv.deraumere;
    int nb_sibur = job->map.width * job->map.height * density_tab[SIBUR]
    - job->global_inv.sibur;

    for (; nb_food > 0; nb_food--)
        add_res_rand(job, FOOD);
    for (; nb_linemate > 0; nb_linemate--)
        add_res_rand(job, LINEMATE);
    for (; nb_der > 0; nb_der--)
        add_res_rand(job, DERAUMERE);
    for (; nb_sibur > 0; nb_sibur--)
        add_res_rand(job, SIBUR);
    gen_other_res(job);
}

void gen_res_tick(job_t *job)
{
    double waiting = (clock() - job->time_gen) / CLOCKS_PER_SEC;

    if (waiting >= (GEN_TICK / job->freq)) {
        gen_res(job);
        job->time_gen = clock();
    }
}
