/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:17:17 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/07 18:17:19 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_all *all, size_t j)
{
	size_t	i;

	if (all->command[j].args[1] != NULL)
	{
		change_exitcode_and_err_msg(all, NO_FILE_OR_DIRECTORY, "127", j);
		return (127);
	}
	i = 0;
	while (all->env[i].name)
	{
		if (!ft_strcmp(all->env[i].name, "?") || !ft_strcmp(all->env[i].name, "$"))
		{
			i++;
			continue ;
		}
		if (ft_strlen(all->env[i].value))
		{
			ft_putstr_fd(all->env[i].name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(all->env[i].value, 1);
		}
		i++;
	}
	change_exitcode_success(all);
	return (1);
}
