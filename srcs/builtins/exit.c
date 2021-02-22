/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:59:05 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/10 09:59:07 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		first_argument_validation(t_all *all, size_t j)
{
	size_t	i;

	i = 0;
	while (all->command[j].args[1][i])
	{
		if (!ft_isdigit(all->command[j].args[1][i]))
		{
			ft_putstr_fd("bash: exit: ", 0);
			ft_putstr_fd(all->command[j].args[1], 1);
			ft_putendl_fd(": numeric argument required", 1);
			delete_environment(all, "?");
			add_environment(all, "?", "255");
			return (255);
		}
		i++;
	}
	return (0);
}

static int		number_of_arguments_validation(t_all *all, size_t j)
{
	if (all->command[j].args[2])
	{
		ft_putstr_fd("bash: exit: ", 1);
		ft_putendl_fd("too many arguments", 1);
		delete_environment(all, "?");
		add_environment(all, "?", "255");
		return (1);
	}
	return (0);
}

int				exit_bash(t_all *all, size_t j)
{
	char	*tmp;
	int		code;

	if (all->command[j].args[1] == NULL)
	{
		delete_environment(all, "?");
		add_environment(all, "?", 0);
		exit(0);
	}
	if (first_argument_validation(all, j))
		exit(255);
	if (number_of_arguments_validation(all, j))
		return (1);
	delete_environment(all, "?");
	code = ft_atoi(all->command[j].args[1]) % 256;
	tmp = ft_itoa(code);
	add_environment(all, "?", tmp);
	free(tmp);
	exit(code);
}
