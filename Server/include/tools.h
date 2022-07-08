/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** tools
*/

#ifndef TOOLS_H
    #define TOOLS_H

    #include <stddef.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>

    #include "client.h"

/**
** @brief Called to get the number of given arguments
** @param args The array of arguments
**/
size_t count_args(char **args);

/**
** @brief Called to store the arguments list in the command's structure
** @param args The array of the arguments given
** @param command The structure containing all the command's informations
**/
void create_args_list(char ***args, char *command);

/**
** @brief Called to free the given array
** @param largs The buffer read by the read function
**/
void free_array(char ***largs);

/**
** @brief Called to transform an int into str
** @param str The str destination
** @param status The int source
**/
char *int_to_str(char *str, int status);

/**
** @brief Called to append a string to another one
** @param dest The buffer read by the read function
** @param src The client who sent the command
**/
void append_to_string(char *dest, char *src);

/**
** @brief Called to check if the command is empty
** @param cmd the string of the command recieved
**/
bool verify_empty(char *cmd);

#endif /* !TOOLS_H */
