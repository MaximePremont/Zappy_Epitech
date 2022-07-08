/*
** EPITECH PROJECT, 2022
** B-YEP-410-LYN-4-1-zappy-maxime.premont
** File description:
** init_teams
*/

#include "server.h"
#include "errors_manager.h"

static void set_default_teams(job_t *infos)
{
    infos->nb_teams = 2;
    infos->teams[0] = strdup("team1");
    infos->teams[1] = strdup("team2");
}

static void fill_teams(int i, int ac, char **av, job_t *infos)
{
    for (i = i + 1; i < ac && av[i] && av[i][0] != '-'; i++) {
        infos->teams = realloc(infos->teams,
        sizeof(char *) * (infos->nb_teams + 1));
        if (infos->teams == NULL)
            show_error("Realloc fail.");
        infos->teams[infos->nb_teams] = strdup(av[i]);
        infos->nb_teams++;
    }
}

void init_teams(int ac, char **av, job_t *infos)
{
    int i = 0;

    for (; i != ac; i++)
        if (strcmp(av[i], "-n") == 0)
            break;
    infos->teams = malloc(sizeof(char *) * 2);
    if (infos->teams == NULL)
        show_error("Malloc fail.");
    infos->nb_teams = 0;
    fill_teams(i, ac, av, infos);
    if (infos->nb_teams == 0)
        set_default_teams(infos);
    infos->teams = realloc(infos->teams,
    sizeof(char *) * (infos->nb_teams + 1));
    if (infos->teams == NULL)
        show_error("Realloc fail.");
    infos->teams[infos->nb_teams] = NULL;
}
