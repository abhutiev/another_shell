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

void				allocate_memory_for_commands(t_all *all)
{
	size_t	i;
	size_t	counter_comm;
	size_t	counter_redir;

	i = 0;
	counter_comm = 0;
	counter_redir = 0;
	while (all->separated_request[i])
	{
		if (!ft_strcmp(all->separated_request[i], "|"))
			counter_comm++;
		else if (!ft_strcmp(all->separated_request[i], ">") ||
				!ft_strcmp(all->separated_request[i], ">>") ||
				!ft_strcmp(all->separated_request[i], "<"))
		{
			counter_redir++;
		}
		i++;
	}
	all->command = (t_command *)ft_calloc(counter_comm + 2, sizeof(t_command));
}

static int			is_pipe(t_all *all, size_t i)
{
	if (!ft_strcmp(all->separated_request[i], "|"))
	{
		free(all->separated_request[i]);
		all->command[all->iter.k].files[all->iter.n].name = NULL;
		all->command[all->iter.k++].args[all->iter.j - 1] = NULL;
		all->iter.j = 0;
		all->iter.n = 0;
		return (1);
	}
	return (0);
}

static int			is_redirect(t_all *all, size_t i)
{
	if (!ft_strcmp(all->separated_request[i], ">>"))
	{
		all->command[all->iter.k].files[all->iter.n].output_flag =
				TO_RIGHT_DOUBLE_REDIR;
		all->command[all->iter.k].files[all->iter.n].name =
				all->separated_request[++all->iter.i];
		free(all->separated_request[i]);
		return (1);
	}
	else if (!ft_strcmp(all->separated_request[i], ">"))
	{
		all->command[all->iter.k].files[all->iter.n].output_flag =
				TO_RIGHT_REDIR;
		all->command[all->iter.k].files[all->iter.n].name =
				all->separated_request[++all->iter.i];
		free(all->separated_request[i]);
		return (1);
	}
	else if (!ft_strcmp(all->separated_request[i], "<"))
	{
		free(all->separated_request[i]);
		all->command[0].files[all->iter.n].name =
				all->separated_request[++all->iter.i];
		all->command[0].files[all->iter.n].output_flag =
				TO_LEFT_REDIR;
		return (1);
	}
	return (0);
}

static void			command_name_filling(t_all *all)
{
	all->command[all->iter.k].args = ft_calloc(20, sizeof(char *));
	all->command[all->iter.k].files = ft_calloc(100, sizeof(t_redirect));
	all->command[all->iter.k].args[all->iter.j++] =
			all->separated_request[all->iter.i];
	all->command[all->iter.k].name =
			all->separated_request[all->iter.i];
}

void				filling_command_structure(t_all *all)
{
	iterators_to_zero(all);
	while (all->separated_request[all->iter.i])
	{
		if (is_pipe(all, all->iter.i))
			all->fd.pipe_flag = 1;
		else if (is_redirect(all, all->iter.i))
			all->iter.n++;
		else
		{
			if (all->iter.j == 0)
				command_name_filling(all);
			else
				all->command[all->iter.k].args[all->iter.j - 1] =
						all->separated_request[all->iter.i];
			all->iter.j++;
		}
		all->iter.i++;
	}
	all->command[all->iter.k].files[all->iter.n].output_flag = STANDART_OUTPUT;
	all->command[all->iter.k].files[all->iter.n].name = NULL;
	all->command[all->iter.k + 1].name = NULL;
}
