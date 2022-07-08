/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** player
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server.h"
#include "player.h"
#include "command.h"

void create_player(player_t *player, char *team_name, job_t *job);
void create_egg(player_t *player, char *team_name,
job_t *job, coords_t coord);

Test(player, create_player)
{
    player_t player;
    job_t job;

    job.next_id = 11;
    job.map.width = 10;
    job.map.height = 10;
    cr_assert_str_empty(player.w_buffer);
    create_player(&player, "team_1", &job);
    cr_assert_eq(player.team_name, "team_1");
    cr_assert_eq(player.id, 11);
    cr_assert_eq(player.state, UNUSED);
    cr_assert_eq(player.level, 1);
    cr_assert_eq(player.time_start, READY_FIRST_COMMAND);
    cr_assert_eq(player.inventory.food, 10);
    cr_assert_eq(player.inventory.linemate, 0);
    cr_assert_eq(player.inventory.deraumere, 0);
    cr_assert_eq(player.inventory.mendiane, 0);
    cr_assert_eq(player.inventory.phiras, 0);
    cr_assert_eq(player.inventory.sibur, 0);
    cr_assert_eq(player.inventory.thystame, 0);
}

Test(player, create_egg)
{
    player_t player;
    coords_t coord = {
        .x = 10,
        .y = 15,
    };
    job_t job;

    job.next_id = 11;
    job.map.width = 10;
    job.map.height = 10;
    create_egg(&player, "team_1", &job, coord);
    cr_assert_str_empty(player.w_buffer);
    cr_assert_eq(player.team_name, "team_1");
    cr_assert_eq(player.id, 11);
    cr_assert_eq(player.state, EGG);
    cr_assert_eq(player.coords.x, 10);
    cr_assert_eq(player.coords.y, 15);
    cr_assert_eq(player.level, 1);
    cr_assert_eq(player.time_start, 600);
    cr_assert_eq(player.time_to_eat, 10000);
    cr_assert_eq(player.inventory.food, 10);
    cr_assert_eq(player.inventory.linemate, 0);
    cr_assert_eq(player.inventory.deraumere, 0);
    cr_assert_eq(player.inventory.mendiane, 0);
    cr_assert_eq(player.inventory.phiras, 0);
    cr_assert_eq(player.inventory.sibur, 0);
    cr_assert_eq(player.inventory.thystame, 0);
}
