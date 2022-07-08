/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** ressources
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "tools.h"

static void free_map(job_t *infos)
{
    for (int i = 0; i != infos->map.width; i++)
        free(infos->map.block[i]);
    free(infos->map.block);
}

Test(inventory, check_ressources)
{
    int nb_food = 0;
    int nb_linemate = 0;
    int nb_deraumere = 0;
    int nb_sibur = 0;
    int nb_mendiane = 0;
    int nb_phiras = 0;
    int nb_thystame = 0;
    job_t job = {
        .map = {
            .height = 10,
            .width = 10,
        },
        .global_inv = {
            .deraumere = 0,
            .food = 0,
            .linemate = 0,
            .mendiane = 0,
            .phiras = 0,
            .sibur = 0,
            .thystame = 0,
        }
    };

    init_map(&job);
    gen_res(&job);
    
    for (int i = 0; i != job.map.width; i++) {
        for (int j = 0; j != job.map.height; j++) {
            nb_food += job.map.block[i][j].food;
            nb_linemate += job.map.block[i][j].linemate;
            nb_deraumere += job.map.block[i][j].deraumere;
            nb_sibur += job.map.block[i][j].sibur;
            nb_mendiane += job.map.block[i][j].mendiane;
            nb_phiras += job.map.block[i][j].phiras;
            nb_thystame += job.map.block[i][j].thystame;
        }
    }

    free_map(&job);
    cr_assert_eq(nb_food, 50);
    cr_assert_eq(nb_linemate, 30);
    cr_assert_eq(nb_deraumere, 15);
    cr_assert_eq(nb_sibur, 10);
    cr_assert_eq(nb_phiras, 8);
    cr_assert_eq(nb_thystame, 5);
    cr_assert_eq(nb_mendiane, 10);
}
