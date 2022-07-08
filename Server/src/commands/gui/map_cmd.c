/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** map_cmd
*/

#include "server.h"

void map_size(player_t *player, char **args, job_t *job)
{
    (void)args;
    (void)player;
    char str[16];

    sprintf(str, "0 msz %d %d\n", job->map.width, job->map.height);
    append_to_gui(job, str);
}

void tile_content(player_t *player, char **args, job_t *job)
{
    (void)player;
    char str[48];
    int x = atoi(args[1]);
    int y = atoi(args[2]);

    sprintf(str, "0 bct %d %d %d %d %d %d %d %d %d\n", x, y,
    job->map.block[y][x].food,
    job->map.block[y][x].linemate,
    job->map.block[y][x].deraumere,
    job->map.block[y][x].sibur,
    job->map.block[y][x].mendiane,
    job->map.block[y][x].phiras,
    job->map.block[y][x].thystame);
    append_to_gui(job, str);
}

void map_content(player_t *player, char **args, job_t *job)
{
    (void)args;
    (void)player;
    char str[256];

    for (int i = 0; i != job->map.height; i++) {
        for (int j = 0; j != job->map.width; j++) {
            sprintf(str, "0 bct %d %d %d %d %d %d %d %d %d\n", j, i,
            job->map.block[i][j].food,
            job->map.block[i][j].linemate,
            job->map.block[i][j].deraumere,
            job->map.block[i][j].sibur,
            job->map.block[i][j].mendiane,
            job->map.block[i][j].phiras,
            job->map.block[i][j].thystame);
            append_to_gui(job, str);
            memset(str, 0, strlen(str));
        }
    }
}

void time_unit(player_t *player, char **args, job_t *job)
{
    (void)args;
    (void)player;
    char str[128];

    sprintf(str, "0 sgt %d\n", job->freq);
    append_to_gui(job, str);
}

void update_tile_inv(int x, int y, inventory_t inv, job_t *job)
{
    char str[128];

    sprintf(str, "%lu bct %d %d %d %d %d %d %d %d %d\n", clock(),
    x, y, inv.food, inv.linemate,
    inv.deraumere, inv.sibur, inv.mendiane, inv.phiras, inv.thystame);
    append_to_gui(job, str);
}
