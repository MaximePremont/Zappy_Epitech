/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** tools
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "tools.h"

Test(tools, append_to_string)
{
    char str[13] = "first";
    char *str_2 = " second";

    append_to_string(str, str_2);
    cr_assert_str_eq(str, "first second");
}

Test(tools, int_to_string)
{
    char str[4];

    int_to_str(str, 1000);
    cr_assert_str_eq(str, "1000");
}

Test(tools, count_args)
{
    char str[2][6] = {
        {"salut"},
        {"hello"},
    };
    int nb_args = count_args((char **)str);

    cr_assert_eq(nb_args, 2);
}
