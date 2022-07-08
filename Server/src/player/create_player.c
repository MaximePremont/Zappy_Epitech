/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** add_player
*/

#include "server.h"
#include <stdlib.h>
#include <time.h>

static void gen_rand_coords(job_t *job, coords_t *coords)
{
    coords->x = rand() % job->map.width;
    coords->y = rand() % job->map.height;
}

static int gen_rand_direction(void)
{
    direction_t direction = UP;

    direction = rand() % 4;
    return direction;
}

void create_player(player_t *player, char *team_name, job_t *job)
{
    player->id = job->next_id;
    player->direction = gen_rand_direction();
    player->time_to_eat = clock();
    player->time_start = READY_FIRST_COMMAND;
    player->level = 1;
    player->state = UNUSED;
    player->team_name = team_name;
    strcpy(player->w_buffer, "");
    for (int i = 0; i < MAX_COMMAND + 1; i++)
        player->command[i] = NULL;
    gen_rand_coords(job, &(player->coords));
    init_inventory(&(player->inventory));
}

void create_egg(player_t *player, char *team_name,
job_t *job, coords_t coord)
{
    player->id = job->next_id;
    player->direction = gen_rand_direction();
    player->time_to_eat = 10000;
    player->time_start = 600;
    player->level = 1;
    player->state = EGG;
    player->team_name = team_name;
    player->coords.x = coord.x;
    player->coords.y = coord.y;
    strcpy(player->w_buffer, "");
    for (int i = 0; i < MAX_COMMAND; i++)
        player->command[i] = NULL;
    init_inventory(&(player->inventory));
}
