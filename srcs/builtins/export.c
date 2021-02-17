/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:57:59 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/10 09:58:01 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	display_export(t_all *all)
{
	size_t	i;

	i = 0;
	while (all->env[i].name)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(all->env[i].name, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(all->env[i].value, 1);
		i++;
	}
	return (1);
}

int			export(t_all *all, size_t j)
{
	size_t	i;
	size_t	k;
	char	**splitted;

	if (all->command[j].args[1] == NULL)
		return (display_export(all));
	i = 1;
	k = 0;
	while (all->command[j].args[i])
	{
		splitted = split(all->command[j].args[i], '=');
		add_environment(all, splitted[0], splitted[1]);
		i++;
	}
	return (1);
}
