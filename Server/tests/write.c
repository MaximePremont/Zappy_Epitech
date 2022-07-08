/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** gui
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "player.h"
#include "command.h"

player_t test_init_player();
void write_player_buffer(client_t *client);
void write_client_buffer(client_t *client);

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(player, write_player_buffer, .init=redirect_all_stdout)
{
    player_t player = test_init_player();
    strcpy(player.w_buffer, "Hello World\n");
    client_t client = {
        .disconnect = 0,
        .player = &player,
        .r_buffer = "",
        .w_buffer = "",
        .addr = {0},
        .fd = 1,
    };

    write_player_buffer(&client);
    cr_assert_stdout_eq_str("Hello World\n");
}

Test(client, write_client_buffer, .init=redirect_all_stdout)
{
    client_t client = {
        .disconnect = 0,
        .player = NULL,
        .r_buffer = "",
        .w_buffer = "",
        .addr = {0},
        .fd = 1,
    };
    strcpy(client.w_buffer, "Salut World\n");

    write_client_buffer(&client);
    cr_assert_stdout_eq_str("Salut World\n");
}
