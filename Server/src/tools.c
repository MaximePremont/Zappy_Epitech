/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** tools
*/

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors_manager.h"

void create_args_list(char ***args, char *command)
{
    char *separator = " ";
    char *token = strtok(command, separator);
    char **command_arr = malloc(sizeof(char *));

    if (command_arr == NULL)
        show_error("Malloc fail");
    command_arr[0] = NULL;
    for (int i = 0; token != NULL; i++) {
        command_arr = realloc(command_arr, sizeof(char *) * (i + 2));
        if (command_arr == NULL)
            show_error("Realloc fail.");
        command_arr[i] = strdup(token);
        command_arr[i + 1] = NULL;
        token = strtok(NULL, separator);
    }
    *args = command_arr;
}

bool verify_empty(char *cmd)
{
    bool empty = true;

    for (size_t i = 0; cmd[i]; i++) {
        if (cmd[i] != ' ') {
            empty = false;
            break;
        }
    }
    return empty;
}

char *int_to_str(char *str, int status)
{
    sprintf(str, "%d", status);
    return str;
}

void append_to_string(char *dest, char *src)
{
    memmove(dest + strlen(dest), src, strlen(src) + 1);
}

size_t count_args(char **args)
{
    size_t count = 0;

    if (args == NULL)
        return count;
    for (; args[count]; count++);
    return count;
}
