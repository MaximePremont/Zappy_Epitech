/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** move_cmd
*/

#include "server.h"

void move_direction(player_t *player, direction_t direction)
{
    if (direction == UP)
        player->coords.y++;
    if (direction == DOWN)
        player->coords.y--;
    if (direction == RIGHT)
        player->coords.x++;
    if (direction == LEFT)
        player->coords.x--;
}

void check_limits(player_t *player, job_t *job)
{
    if (player->coords.x < 0)
        player->coords.x = job->map.width - 1;
    if (player->coords.x == job->map.width)
        player->coords.x = 0;
    if (player->coords.y < 0)
        player->coords.y = job->map.height - 1;
    if (player->coords.y == job->map.height)
        player->coords.y = 0;
}

void forward(player_t *player, char **args, job_t *job)
{
    (void)args;

    move_direction(player, player->direction);
    check_limits(player, job);
    append_to_string(player->w_buffer, "ok\n");
}

void right(player_t *player, char **args, job_t *job)
{
    (void)job;
    (void)args;
    bool change = false;

    if (player->direction == UP && !change) {
        player->direction = RIGHT;
        change = true;
    }
    if (player->direction == DOWN && !change) {
        player->direction = LEFT;
        change = true;
    }
    if (player->direction == RIGHT && !change) {
        player->direction = DOWN;
        change = true;
    }
    if (player->direction == LEFT && !change)
        player->direction = UP;
    append_to_string(player->w_buffer, "ok\n");
}

void left(player_t *player, char **args, job_t *job)
{
    (void)job;
    (void)args;
    bool change = false;

    if (player->direction == DOWN && !change) {
        player->direction = RIGHT;
        change = true;
    }
    if (player->direction == RIGHT && !change) {
        player->direction = UP;
        change = true;
    }
    if (player->direction == LEFT && !change) {
        player->direction = DOWN;
        change = true;
    }
    if (player->direction == UP && !change)
        player->direction = LEFT;
    append_to_string(player->w_buffer, "ok\n");
}
