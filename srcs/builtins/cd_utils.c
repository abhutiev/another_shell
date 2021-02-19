/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 09:36:11 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/19 09:36:13 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			get_ready_for_cd(t_all *all, t_cd *cd, size_t j)
{
	cd->i = 0;
	cd->tmp = getcwd(NULL, -1);
	cd->splitted_path = split(cd->tmp, '/');
	free(cd->tmp);
	cd->splitted_directories = split(all->command[j].args[1], '/');
	if (all->command[j].args[1][0] == '~')
	{
		free(cd->splitted_directories[0]);
		cd->i++;
	}
}

void			cd_up(t_cd *cd)
{
	cd->k = 0;
	while (cd->splitted_path[cd->k])
		cd->k++;
	if (cd->k == 0)
	{
		free(cd->splitted_directories[cd->i]);
		return ;
	}
	free(cd->splitted_path[cd->k - 1]);
	cd->splitted_path[cd->k - 1] = NULL;
	free(cd->splitted_directories[cd->i]);
}

void			memory_cleaning_and_forming_of_path(t_cd *cd)
{
	free(cd->splitted_directories);
	cd->k = 0;
	cd->path = ft_calloc(1, 1);
	while (cd->splitted_path[cd->k])
	{
		cd->tmp = cd->path;
		cd->path = strjoin_for_path(cd->path, cd->splitted_path[cd->k]);
		free(cd->splitted_path[cd->k++]);
		free(cd->tmp);
	}
	free(cd->splitted_path);
	if (cd->k == 0)
	{
		chdir("/");
		free(cd->path);
		return ;
	}
}

int		cd_from_current_directory(t_all *all, size_t j)
{
	t_cd	cd;

	get_ready_for_cd(all, &cd, j);
	while (cd.splitted_directories[cd.i])
	{
		if (!ft_strcmp("..", cd.splitted_directories[cd.i]))
			cd_up(&cd);
		else if (!ft_strcmp(".", cd.splitted_directories[cd.i]))
			free(cd.splitted_directories[cd.i]);
		else
		{
			cd.k = 0;
			while (cd.splitted_path[cd.k])
				cd.k++;
			cd.splitted_path[cd.k] = cd.splitted_directories[cd.i];
		}
		cd.i++;
	}
	memory_cleaning_and_forming_of_path(&cd);
	if (chdir(cd.path) == -1)
	{
		ft_putstr_fd("bash: cd: ", 0);
		ft_putstr_fd(all->command[j].args[1], 0);
		ft_putendl_fd(" :No such file or directory", 0);
		return (2);
	}
	free(cd.path);
	return (1);
}
