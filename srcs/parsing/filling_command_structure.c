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

void	free_command_names(t_all *all)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (all->separated_request[i])
		i++;
	free(all->separated_request[i]);
	i = 0;
	while (all->command[i].name)
	{
		j = 0;
		while (all->command[i].args[j])
		{
			free(all->command[i].args[j]);
			j++;
		}
		free(all->command[i].args[j]);
		free(all->command[i].name);
		free(all->command[i].args);
		i++;
	}
	free(all->command[i].args);
	free(all->command[i].name);
	free(all->separated_request);
	free(all->command);
}

void	allocate_memory_for_commands(t_all *all)
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

void	filling_command_structure(t_all *all)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = 0;
	k = 0;
	while (all->separated_request[i])
	{
		if (!ft_strcmp(all->separated_request[i], ">") || !ft_strcmp(all->separated_request[i], ">>") || !ft_strcmp(all->separated_request[i], "<") || !ft_strcmp(all->separated_request[i], "|"))
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