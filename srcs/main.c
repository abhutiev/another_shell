/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 03:41:25 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/04 03:41:27 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int 	single_command_execution(t_all *all, size_t j)
{
	if (!open_file_descriptors(all, j))
	{
		if (!builtin_execution(all, j))
:wq	}
	else
		return (1);
	close_file_descriptors(all, j);
	return (0);
}

void	build_pipeline(t_all *all)
{
	size_t	j;
	all->fd.number_of_pipes = 0;
	while (all->command[all->fd.number_of_pipes].name)
		all->fd.number_of_pipes++;
	all->fd.pipeline = ft_calloc(all->fd.number_of_pipes--, sizeof(int) * 2);
	j = 0;
	while (j < all->fd.number_of_pipes)
	{
		all->fd.pipeline[j] = ft_calloc(2, sizeof(int));
		pipe(all->fd.pipeline[j]);
		j++;
	}
}

int		multiple_command_execution(t_all *all)
{
	pid_t	pid;
	size_t	j;

	j = 0;
	build_pipeline(all);
	while (all->command[j].name)
	{

		if (single_command_execution(all, j))
			return (1);
		j++;
	}
	return (0);
}

int 	request_execution(t_all *all)
{

	if (!all->fd.pipe_flag)
		return (single_command_execution(all, 0));
	return (multiple_command_execution(all));
}

int		main(int argc, char **argv, char **en)
{
	t_all	all;

	pregame_ritual(&all, argc, argv, en);
	while (1)
	{
		write(1, SHELL_NAME, ft_strlen(SHELL_NAME));
		get_next_line(0, &(all.buffer.line_1));
		count_requests(&all);
		separate_requests(&all);
		if (validation_of_requests(&all))
		{
			free_memory_in_case_of_invalid_request(&all);
			continue ;
		}
		parsing_and_execution(&all);
	}
	return (0);
}
