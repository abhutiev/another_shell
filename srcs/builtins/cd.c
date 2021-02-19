/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:57:10 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/10 09:57:12 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		cd_to_home(t_all *all)
{
	add_environment(all, "OLDPWD", look_for_env(all, "PWD"));
	chdir(look_for_env(all, "HOME"));
	add_environment(all, "PWD", look_for_env(all, "HOME"));
	return (1);
}

static int		cd_last(t_all *all)
{
	char	*tmp1;
	char	*tmp2;

	chdir(look_for_env(all,"OLDPWD"));
	tmp1 = ft_strdup(look_for_env(all, "PWD"));
	tmp2 = ft_strdup(look_for_env(all, "OLDPWD"));
	delete_environment(all, "PWD");
	delete_environment(all, "OLDPWD");
	add_environment(all, "PWD", tmp2);
	add_environment(all, "OLDPWD", tmp1);
	free(tmp1);
	free(tmp2);
	return (1);
}

static int 		cd_from_home_directory(t_all *all)
{

	return (1);
}

static int 		cd_from_root_directory(t_all *all)
{
	return (1);
}

static int		cd_from_current_directory(t_all *all)
{
	return (1);
}

int				cd(t_all *all, size_t j)
{
	if (all->command[j].args[1] == NULL)
		return (cd_to_home(all));
	else if (!ft_strcmp(all->command[j].args[1], "-"))
		return (cd_last(all));
	else if (all->command[j].args[1][0] == '/')
		return (cd_from_home_directory(all));
	else if (all->command[j].args[1][0] == '~')
		return (cd_from_root_directory(all));
	else
		return (cd_from_current_directory(all));
	return (1);
}