/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** client
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server.h"

void create_player(player_t *player, char *team_name, job_t *job);

Test(client, create_client)
{
    client_t client;
    sockaddr_in_t sockaddr;

    init_client(&client, 12, sockaddr);

    cr_assert_eq(client.disconnect, 0);
    cr_assert_eq(client.fd, 12);
    cr_assert_eq(client.player, NULL);
    cr_assert_str_empty(client.r_buffer);
    cr_assert_str_empty(client.w_buffer);
}
