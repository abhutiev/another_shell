/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_environments.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:08:55 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/04 07:08:56 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_environments(t_all *all, char **env)
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
}

void	add_environment(t_all *all, char *name, char *value)
{
	size_t	i;
	size_t	number_of_envs;

	i = 0;
	number_of_envs = 0;
	while (all->env[number_of_envs].name)
		number_of_envs++;
	while (all->env[i].name && (ft_strcmp(all->env[i].name, name) > 0))
		i++;
	while (number_of_envs + 1> i)
	{
		all->env[number_of_envs + 1].name = all->env[number_of_envs].name;
		all->env[number_of_envs + 1].value = all->env[number_of_envs].value;
		number_of_envs--;
	}
	all->env[number_of_envs + 1].name = ft_strdup(name);
	all->env[number_of_envs + 1].value = ft_strdup(value);
}

void	sort_environments(t_all *all)
{
	int 	i;
	int 	j;
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

void	delete_environment(t_all *all, char *name)
{
	size_t	i;

	i = 0;
	while (all->env[i].name && (ft_strcmp(all->env[i].name, name) != 0))
	{
		i++;
	}
	if (all->env[i].name == 0)
		return ;
	free(all->env[i].name);
	free(all->env[i].value);
	while (all->env[i + 1].name)
	{
		all->env[i].name = all->env[i + 1].name;
		all->env[i].value = all->env[i + 1].value;
		i++;
	}
	all->env[i].name = NULL;
	all->env[i].value = NULL;
}

void	display_env(t_all *all)
{
	size_t	i;

	i = 0;
	while (all->env[i].name)
	{
		printf("%s=%s\n", all->env[i].name, all->env[i].value);
		i++;
	}
}
