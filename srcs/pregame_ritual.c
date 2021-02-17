/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pregame_ritual_up.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 03:41:25 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/04 03:41:27 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	flags_shutting_up(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

static void	save_fd(t_all *all)
{
	all->fd.standard_input = dup(0);
	all->fd.standard_output = dup(1);
}

void		sort_environments(t_all *all)
{
	int		i;
	int		j;
	size_t	number_of_envs;
	char	*tmp;

	i = -1;
	number_of_envs = 0;
	while (all->env[number_of_envs].name)
		number_of_envs++;
	while (++i < number_of_envs)
	{
		j = -1;
		while (++j < number_of_envs - i - 1)
			if (ft_strcmp(all->env[j].name, all->env[j + 1].name) < 0)
			{
				tmp = all->env[j].name;
				all->env[j].name = all->env[j + 1].name;
				all->env[j + 1].name = tmp;
				tmp = all->env[j].value;
				all->env[j].value = all->env[j + 1].value;
				all->env[j + 1].value = tmp;
			}
	}
}

void		load_environments(t_all *all, char **env)
{
	size_t	i;
	size_t	number_of_envs;
	char	**tmp;

	i = 0;
	number_of_envs = 0;
	while (env[number_of_envs])
	{
		number_of_envs++;
	}
	all->env = (t_env *)ft_calloc(number_of_envs + 100, sizeof(t_env));
	while (env[i])
	{
		tmp = split(env[i], '=');
		all->env[i].name = tmp[0];
		all->env[i].value = tmp[1];
		free(tmp[2]);
		free(tmp);
		i++;
	}
	sort_environments(all);
}

void		pregame_ritual(t_all *all, int ac, char **av, char **env)
{
	flags_shutting_up(ac, av);
	load_environments(all, env);
	save_fd(all);
	dup2(0, all->fd.standard_input);
	dup2(1, all->fd.standard_output);
}
