/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleaning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:24:09 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/14 19:24:11 by gdoge            ###   ########.fr       */
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
		j = 1;
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

void	clean_after_yourself(t_all *all, size_t i)
{
	free(all->requests.separated[i]);
	free(all->requests.separated);
	free(all->requests.line_with_substitutions[i]);
	free(all->requests.line_with_substitutions);
}