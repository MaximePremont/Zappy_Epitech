/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** broadcast_cmd
*/

#include "server.h"

static int absolute(int n)
{
    if (n < 0)
        n *= -1;
    return n;
}

static int get_shorter(int x1, int x2, int full_length)
{
    int res = x2 - x1;

    if (absolute(res) > full_length / 2 && res > 0)
        res = res - full_length;
    if (absolute(res) > full_length / 2 && res < 0)
        res = full_length + res;
    return res;
}

orientation_t get_ori(int x, int y, coords_t reciever, coords_t sender)
{
    if (reciever.x == sender.x && reciever.y == sender.y)
        return SAME;
    if (y > 0 && sender.x == reciever.x)
        return DOWN_CENTER;
    if (y < 0 && sender.x == reciever.x)
        return UP_CENTER;
    if (sender.y == reciever.y && x > 0)
        return CENTER_LEFT;
    if (sender.y == reciever.y && x < 0)
        return CENTER_RIGHT;
    if (y > 0 && x > 0)
        return DOWN_LEFT;
    if (y > 0 && x < 0)
        return DOWN_RIGHT;
    if (y < 0 && x > 0)
        return UP_LEFT;
    if (y < 0 && x < 0)
        return UP_RIGHT;
    return SAME;
}

static int get_direction_sound(direction_t direction, coords_t reciever,
coords_t sender, job_t *job)
{
    orientation_t res;
    int x = get_shorter(sender.x, reciever.x, job->map.width);
    int y = get_shorter(sender.y, reciever.y, job->map.height);

    res = get_ori(x, y, reciever, sender);
    if (res == SAME)
        return res;
    if (direction == RIGHT)
        res += 2;
    if (direction == DOWN)
        res += 4;
    if (direction == LEFT)
        res += 6;
    if (res > 8)
        res -= 8;
    return res;
}

void broadcast(player_t *player, char **args, job_t *job)
{
    linked_player_t *tmp = job->head_player;
    char str[128];

    if (args == NULL || args[1] == NULL)
        return;
    while (tmp != NULL) {
        if (tmp->player.id != player->id && tmp->player.state == ALIVE) {
            sprintf(str, "message %d, ",
            get_direction_sound(tmp->player.direction,
            tmp->player.coords, player->coords, job));
            append_to_string(tmp->player.w_buffer, str);
            append_to_string(tmp->player.w_buffer, args[1]);
            append_to_string(tmp->player.w_buffer, "\n");
        }
        tmp = tmp->next;
    }
    append_to_string(player->w_buffer, "ok\n");
}
