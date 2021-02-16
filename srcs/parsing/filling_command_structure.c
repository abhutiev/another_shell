/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_command_structure.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:16:01 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/14 19:16:03 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		allocate_memory_for_commands(t_all *all)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (all->separated_request[i])
	{
		if (!ft_strcmp(all->separated_request[i], ">") ||
			!ft_strcmp(all->separated_request[i], ">>") ||
			!ft_strcmp(all->separated_request[i], "<") ||
			!ft_strcmp(all->separated_request[i], "|"))
			counter++;
		i++;
	}
	all->command = (t_command *)ft_calloc(counter + 2, sizeof(t_command));
}

static int	is_pipe_or_redirect(t_all *all, size_t i)
{
	if (!ft_strcmp(all->separated_request[i], ">") ||
		!ft_strcmp(all->separated_request[i], ">>") ||
			!ft_strcmp(all->separated_request[i], "<") ||
				!ft_strcmp(all->separated_request[i], "|"))
		return (1);
	return (0);
}

void		filling_command_structure(t_all *all)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = 0;
	k = 0;
	while (all->separated_request[i])
	{
		if (is_pipe_or_redirect(all, i))
		{
			free(all->separated_request[i]);
			all->command[k].args[j - 1] = NULL;
			k++;
			j = 0;
		}
		else
		{
			if (j == 0)
			{
				all->command[k].args = ft_calloc(20, sizeof(char *));
				all->command[k].args[j++
				] = all->separated_request[i];
				all->command[k].name = all->separated_request[i];
			}
			else
				all->command[k].args[j - 1] = all->separated_request[i];
			j++;
		}
		i++;
	}
	all->command[k + 1].name = NULL;
}