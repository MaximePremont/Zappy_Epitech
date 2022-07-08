/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "player.h"
#include "command.h"

player_t test_init_player()
{
    player_t player = {
        .id = 0,
        .team_name = "team_1",
        .coords = {0, 0},
        .direction = UP,
        .inventory = {
            .food = 0,
            .linemate = 0,
            .deraumere = 0,
            .sibur = 0,
            .mendiane = 0,
            .phiras = 0,
            .thystame = 0,
        },
        .state = ALIVE,
        .level = 0,
        .time_to_eat = 0,
        .time_start = 0,
        .w_buffer = ""
    };

    return player;
}

Test(player, left_direction)
{
    player_t player = test_init_player();

    left(&player, NULL, NULL);
    cr_assert_eq(player.direction, LEFT);
    left(&player, NULL, NULL);
    cr_assert_eq(player.direction, DOWN);
    left(&player, NULL, NULL);
    cr_assert_eq(player.direction, RIGHT);
    left(&player, NULL, NULL);
    cr_assert_eq(player.direction, UP);
}

Test(player, right_direction)
{
    player_t player = test_init_player();

    right(&player, NULL, NULL);
    cr_assert_eq(player.direction, RIGHT);
    right(&player, NULL, NULL);
    cr_assert_eq(player.direction, DOWN);
    right(&player, NULL, NULL);
    cr_assert_eq(player.direction, LEFT);
    right(&player, NULL, NULL);
    cr_assert_eq(player.direction, UP);
}
